// A Bison parser, made by GNU Bison 3.2.1.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file dhcp6_parser.h
 ** Define the isc::dhcp::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_PARSER6_DHCP6_PARSER_H_INCLUDED
# define YY_PARSER6_DHCP6_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 17 "dhcp6_parser.yy" // lalr1.cc:404

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp6/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 60 "dhcp6_parser.h" // lalr1.cc:404

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

// Support move semantics when possible.
#if defined __cplusplus && 201103L <= __cplusplus
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef PARSER6_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSER6_DEBUG 1
#  else
#   define PARSER6_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSER6_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSER6_DEBUG */

#line 14 "dhcp6_parser.yy" // lalr1.cc:404
namespace isc { namespace dhcp {
#line 162 "dhcp6_parser.h" // lalr1.cc:404

  /// A stack with random access from its top.
  template <typename T, typename S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;
    typedef typename S::size_type size_type;
<<<<<<< HEAD

    stack (size_type n = 200)
      : seq_ (n)
    {}

=======

    stack (size_type n = 200)
      : seq_ (n)
    {}

>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (size_type i)
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (int i)
    {
      return operator[] (size_type (i));
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (size_type i) const
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (int i) const
    {
      return operator[] (size_type (i));
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    void
    push (YY_MOVE_REF (T) t)
    {
      seq_.push_back (T ());
      operator[](0).move (t);
    }

    void
    pop (int n = 1)
    {
      for (; 0 < n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    size_type
    size () const
    {
      return seq_.size ();
    }

    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <typename T, typename S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, int range)
      : stack_ (stack)
      , range_ (range)
    {}

    const T&
    operator[] (int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    int range_;
  };



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename U>
    T&
    emplace (U&& u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u));
    }
# else
    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
# if defined __cplusplus && 201103L <= __cplusplus
      emplace<T> (std::move (other.as<T> ()));
# else
      emplace<T> ();
      swap<T> (other);
# endif
      other.destroy<T> ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Move the content of \a other to this.
    template <typename T>
    void
    move (self_type&& other)
    {
      emplace<T> (std::move (other.as<T> ()));
      other.destroy<T> ();
    }
#endif

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      emplace<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Dhcp6Parser
  {
  public:
#ifndef PARSER6_STYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // value
      // map_value
      // db_type
      // hr_mode
      // duid_type
      // ncr_protocol_value
      // replace_client_name_value
      char dummy1[sizeof (ElementPtr)];

      // "boolean"
      char dummy2[sizeof (bool)];

      // "floating point"
      char dummy3[sizeof (double)];

      // "integer"
      char dummy4[sizeof (int64_t)];

      // "constant string"
      char dummy5[sizeof (std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof (union_type)> semantic_type;
#else
    typedef PARSER6_STYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_COMMA = 258,
        TOKEN_COLON = 259,
        TOKEN_LSQUARE_BRACKET = 260,
        TOKEN_RSQUARE_BRACKET = 261,
        TOKEN_LCURLY_BRACKET = 262,
        TOKEN_RCURLY_BRACKET = 263,
        TOKEN_NULL_TYPE = 264,
        TOKEN_DHCP6 = 265,
        TOKEN_DATA_DIRECTORY = 266,
        TOKEN_CONFIG_CONTROL = 267,
        TOKEN_CONFIG_DATABASES = 268,
        TOKEN_CONFIG_FETCH_WAIT_TIME = 269,
        TOKEN_INTERFACES_CONFIG = 270,
        TOKEN_INTERFACES = 271,
        TOKEN_RE_DETECT = 272,
        TOKEN_LEASE_DATABASE = 273,
        TOKEN_HOSTS_DATABASE = 274,
        TOKEN_HOSTS_DATABASES = 275,
        TOKEN_TYPE = 276,
        TOKEN_MEMFILE = 277,
        TOKEN_MYSQL = 278,
        TOKEN_POSTGRESQL = 279,
        TOKEN_CQL = 280,
        TOKEN_USER = 281,
        TOKEN_PASSWORD = 282,
        TOKEN_HOST = 283,
        TOKEN_PORT = 284,
        TOKEN_PERSIST = 285,
        TOKEN_LFC_INTERVAL = 286,
        TOKEN_READONLY = 287,
        TOKEN_CONNECT_TIMEOUT = 288,
        TOKEN_CONTACT_POINTS = 289,
        TOKEN_MAX_RECONNECT_TRIES = 290,
        TOKEN_RECONNECT_WAIT_TIME = 291,
        TOKEN_KEYSPACE = 292,
        TOKEN_CONSISTENCY = 293,
        TOKEN_SERIAL_CONSISTENCY = 294,
        TOKEN_REQUEST_TIMEOUT = 295,
        TOKEN_TCP_KEEPALIVE = 296,
        TOKEN_TCP_NODELAY = 297,
<<<<<<< HEAD
<<<<<<< HEAD
        TOKEN_PREFERRED_LIFETIME = 298,
        TOKEN_MIN_PREFERRED_LIFETIME = 299,
        TOKEN_MAX_PREFERRED_LIFETIME = 300,
        TOKEN_VALID_LIFETIME = 301,
        TOKEN_MIN_VALID_LIFETIME = 302,
        TOKEN_MAX_VALID_LIFETIME = 303,
        TOKEN_RENEW_TIMER = 304,
        TOKEN_REBIND_TIMER = 305,
        TOKEN_CALCULATE_TEE_TIMES = 306,
        TOKEN_T1_PERCENT = 307,
        TOKEN_T2_PERCENT = 308,
        TOKEN_DECLINE_PROBATION_PERIOD = 309,
        TOKEN_SERVER_TAG = 310,
        TOKEN_SUBNET6 = 311,
        TOKEN_OPTION_DEF = 312,
        TOKEN_OPTION_DATA = 313,
        TOKEN_NAME = 314,
        TOKEN_DATA = 315,
        TOKEN_CODE = 316,
        TOKEN_SPACE = 317,
        TOKEN_CSV_FORMAT = 318,
        TOKEN_ALWAYS_SEND = 319,
        TOKEN_RECORD_TYPES = 320,
        TOKEN_ENCAPSULATE = 321,
        TOKEN_ARRAY = 322,
        TOKEN_POOLS = 323,
        TOKEN_POOL = 324,
        TOKEN_PD_POOLS = 325,
        TOKEN_PREFIX = 326,
        TOKEN_PREFIX_LEN = 327,
        TOKEN_EXCLUDED_PREFIX = 328,
        TOKEN_EXCLUDED_PREFIX_LEN = 329,
        TOKEN_DELEGATED_LEN = 330,
        TOKEN_USER_CONTEXT = 331,
        TOKEN_COMMENT = 332,
        TOKEN_SUBNET = 333,
        TOKEN_INTERFACE = 334,
        TOKEN_INTERFACE_ID = 335,
        TOKEN_ID = 336,
        TOKEN_RAPID_COMMIT = 337,
        TOKEN_RESERVATION_MODE = 338,
        TOKEN_DISABLED = 339,
        TOKEN_OUT_OF_POOL = 340,
        TOKEN_GLOBAL = 341,
        TOKEN_ALL = 342,
        TOKEN_SHARED_NETWORKS = 343,
        TOKEN_MAC_SOURCES = 344,
        TOKEN_RELAY_SUPPLIED_OPTIONS = 345,
        TOKEN_HOST_RESERVATION_IDENTIFIERS = 346,
        TOKEN_SANITY_CHECKS = 347,
        TOKEN_LEASE_CHECKS = 348,
        TOKEN_CLIENT_CLASSES = 349,
        TOKEN_REQUIRE_CLIENT_CLASSES = 350,
        TOKEN_TEST = 351,
        TOKEN_ONLY_IF_REQUIRED = 352,
        TOKEN_CLIENT_CLASS = 353,
        TOKEN_RESERVATIONS = 354,
        TOKEN_IP_ADDRESSES = 355,
        TOKEN_PREFIXES = 356,
        TOKEN_DUID = 357,
        TOKEN_HW_ADDRESS = 358,
        TOKEN_HOSTNAME = 359,
        TOKEN_FLEX_ID = 360,
        TOKEN_RELAY = 361,
        TOKEN_IP_ADDRESS = 362,
        TOKEN_HOOKS_LIBRARIES = 363,
        TOKEN_LIBRARY = 364,
        TOKEN_PARAMETERS = 365,
        TOKEN_EXPIRED_LEASES_PROCESSING = 366,
        TOKEN_RECLAIM_TIMER_WAIT_TIME = 367,
        TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 368,
        TOKEN_HOLD_RECLAIMED_TIME = 369,
        TOKEN_MAX_RECLAIM_LEASES = 370,
        TOKEN_MAX_RECLAIM_TIME = 371,
        TOKEN_UNWARNED_RECLAIM_CYCLES = 372,
        TOKEN_SERVER_ID = 373,
        TOKEN_LLT = 374,
        TOKEN_EN = 375,
        TOKEN_LL = 376,
        TOKEN_IDENTIFIER = 377,
        TOKEN_HTYPE = 378,
        TOKEN_TIME = 379,
        TOKEN_ENTERPRISE_ID = 380,
        TOKEN_DHCP4O6_PORT = 381,
        TOKEN_CONTROL_SOCKET = 382,
        TOKEN_SOCKET_TYPE = 383,
        TOKEN_SOCKET_NAME = 384,
        TOKEN_DHCP_QUEUE_CONTROL = 385,
        TOKEN_DHCP_DDNS = 386,
        TOKEN_ENABLE_UPDATES = 387,
        TOKEN_QUALIFYING_SUFFIX = 388,
        TOKEN_SERVER_IP = 389,
        TOKEN_SERVER_PORT = 390,
        TOKEN_SENDER_IP = 391,
        TOKEN_SENDER_PORT = 392,
        TOKEN_MAX_QUEUE_SIZE = 393,
        TOKEN_NCR_PROTOCOL = 394,
        TOKEN_NCR_FORMAT = 395,
        TOKEN_OVERRIDE_NO_UPDATE = 396,
        TOKEN_OVERRIDE_CLIENT_UPDATE = 397,
        TOKEN_REPLACE_CLIENT_NAME = 398,
        TOKEN_GENERATED_PREFIX = 399,
        TOKEN_UDP = 400,
        TOKEN_TCP = 401,
        TOKEN_JSON = 402,
        TOKEN_WHEN_PRESENT = 403,
        TOKEN_NEVER = 404,
        TOKEN_ALWAYS = 405,
        TOKEN_WHEN_NOT_PRESENT = 406,
        TOKEN_HOSTNAME_CHAR_SET = 407,
        TOKEN_HOSTNAME_CHAR_REPLACEMENT = 408,
        TOKEN_LOGGING = 409,
        TOKEN_LOGGERS = 410,
        TOKEN_OUTPUT_OPTIONS = 411,
        TOKEN_OUTPUT = 412,
        TOKEN_DEBUGLEVEL = 413,
        TOKEN_SEVERITY = 414,
        TOKEN_FLUSH = 415,
        TOKEN_MAXSIZE = 416,
        TOKEN_MAXVER = 417,
        TOKEN_PATTERN = 418,
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        TOKEN_MAX_ROW_ERRORS = 298,
        TOKEN_PREFERRED_LIFETIME = 299,
        TOKEN_MIN_PREFERRED_LIFETIME = 300,
        TOKEN_MAX_PREFERRED_LIFETIME = 301,
        TOKEN_VALID_LIFETIME = 302,
        TOKEN_MIN_VALID_LIFETIME = 303,
        TOKEN_MAX_VALID_LIFETIME = 304,
        TOKEN_RENEW_TIMER = 305,
        TOKEN_REBIND_TIMER = 306,
        TOKEN_CALCULATE_TEE_TIMES = 307,
        TOKEN_T1_PERCENT = 308,
        TOKEN_T2_PERCENT = 309,
        TOKEN_DECLINE_PROBATION_PERIOD = 310,
        TOKEN_SERVER_TAG = 311,
        TOKEN_SUBNET6 = 312,
        TOKEN_OPTION_DEF = 313,
        TOKEN_OPTION_DATA = 314,
        TOKEN_NAME = 315,
        TOKEN_DATA = 316,
        TOKEN_CODE = 317,
        TOKEN_SPACE = 318,
        TOKEN_CSV_FORMAT = 319,
        TOKEN_ALWAYS_SEND = 320,
        TOKEN_RECORD_TYPES = 321,
        TOKEN_ENCAPSULATE = 322,
        TOKEN_ARRAY = 323,
        TOKEN_POOLS = 324,
        TOKEN_POOL = 325,
        TOKEN_PD_POOLS = 326,
        TOKEN_PREFIX = 327,
        TOKEN_PREFIX_LEN = 328,
        TOKEN_EXCLUDED_PREFIX = 329,
        TOKEN_EXCLUDED_PREFIX_LEN = 330,
        TOKEN_DELEGATED_LEN = 331,
        TOKEN_USER_CONTEXT = 332,
        TOKEN_COMMENT = 333,
        TOKEN_SUBNET = 334,
        TOKEN_INTERFACE = 335,
        TOKEN_INTERFACE_ID = 336,
        TOKEN_ID = 337,
        TOKEN_RAPID_COMMIT = 338,
        TOKEN_RESERVATION_MODE = 339,
        TOKEN_DISABLED = 340,
        TOKEN_OUT_OF_POOL = 341,
        TOKEN_GLOBAL = 342,
        TOKEN_ALL = 343,
        TOKEN_SHARED_NETWORKS = 344,
        TOKEN_MAC_SOURCES = 345,
        TOKEN_RELAY_SUPPLIED_OPTIONS = 346,
        TOKEN_HOST_RESERVATION_IDENTIFIERS = 347,
        TOKEN_SANITY_CHECKS = 348,
        TOKEN_LEASE_CHECKS = 349,
        TOKEN_CLIENT_CLASSES = 350,
        TOKEN_REQUIRE_CLIENT_CLASSES = 351,
        TOKEN_TEST = 352,
        TOKEN_ONLY_IF_REQUIRED = 353,
        TOKEN_CLIENT_CLASS = 354,
        TOKEN_RESERVATIONS = 355,
        TOKEN_IP_ADDRESSES = 356,
        TOKEN_PREFIXES = 357,
        TOKEN_DUID = 358,
        TOKEN_HW_ADDRESS = 359,
        TOKEN_HOSTNAME = 360,
        TOKEN_FLEX_ID = 361,
        TOKEN_RELAY = 362,
        TOKEN_IP_ADDRESS = 363,
        TOKEN_HOOKS_LIBRARIES = 364,
        TOKEN_LIBRARY = 365,
        TOKEN_PARAMETERS = 366,
        TOKEN_EXPIRED_LEASES_PROCESSING = 367,
        TOKEN_RECLAIM_TIMER_WAIT_TIME = 368,
        TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 369,
        TOKEN_HOLD_RECLAIMED_TIME = 370,
        TOKEN_MAX_RECLAIM_LEASES = 371,
        TOKEN_MAX_RECLAIM_TIME = 372,
        TOKEN_UNWARNED_RECLAIM_CYCLES = 373,
        TOKEN_SERVER_ID = 374,
        TOKEN_LLT = 375,
        TOKEN_EN = 376,
        TOKEN_LL = 377,
        TOKEN_IDENTIFIER = 378,
        TOKEN_HTYPE = 379,
        TOKEN_TIME = 380,
        TOKEN_ENTERPRISE_ID = 381,
        TOKEN_DHCP4O6_PORT = 382,
        TOKEN_CONTROL_SOCKET = 383,
        TOKEN_SOCKET_TYPE = 384,
        TOKEN_SOCKET_NAME = 385,
        TOKEN_DHCP_QUEUE_CONTROL = 386,
        TOKEN_DHCP_DDNS = 387,
        TOKEN_ENABLE_UPDATES = 388,
        TOKEN_QUALIFYING_SUFFIX = 389,
        TOKEN_SERVER_IP = 390,
        TOKEN_SERVER_PORT = 391,
        TOKEN_SENDER_IP = 392,
        TOKEN_SENDER_PORT = 393,
        TOKEN_MAX_QUEUE_SIZE = 394,
        TOKEN_NCR_PROTOCOL = 395,
        TOKEN_NCR_FORMAT = 396,
        TOKEN_OVERRIDE_NO_UPDATE = 397,
        TOKEN_OVERRIDE_CLIENT_UPDATE = 398,
        TOKEN_REPLACE_CLIENT_NAME = 399,
        TOKEN_GENERATED_PREFIX = 400,
        TOKEN_UDP = 401,
        TOKEN_TCP = 402,
        TOKEN_JSON = 403,
        TOKEN_WHEN_PRESENT = 404,
        TOKEN_NEVER = 405,
        TOKEN_ALWAYS = 406,
        TOKEN_WHEN_NOT_PRESENT = 407,
        TOKEN_HOSTNAME_CHAR_SET = 408,
        TOKEN_HOSTNAME_CHAR_REPLACEMENT = 409,
        TOKEN_LOGGING = 410,
        TOKEN_LOGGERS = 411,
        TOKEN_OUTPUT_OPTIONS = 412,
        TOKEN_OUTPUT = 413,
        TOKEN_DEBUGLEVEL = 414,
        TOKEN_SEVERITY = 415,
        TOKEN_FLUSH = 416,
        TOKEN_MAXSIZE = 417,
        TOKEN_MAXVER = 418,
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
        TOKEN_DHCP4 = 419,
        TOKEN_DHCPDDNS = 420,
        TOKEN_CONTROL_AGENT = 421,
        TOKEN_TOPLEVEL_JSON = 422,
        TOKEN_TOPLEVEL_DHCP6 = 423,
        TOKEN_SUB_DHCP6 = 424,
        TOKEN_SUB_INTERFACES6 = 425,
        TOKEN_SUB_SUBNET6 = 426,
        TOKEN_SUB_POOL6 = 427,
        TOKEN_SUB_PD_POOL = 428,
        TOKEN_SUB_RESERVATION = 429,
        TOKEN_SUB_OPTION_DEFS = 430,
        TOKEN_SUB_OPTION_DEF = 431,
        TOKEN_SUB_OPTION_DATA = 432,
        TOKEN_SUB_HOOKS_LIBRARY = 433,
        TOKEN_SUB_DHCP_DDNS = 434,
        TOKEN_SUB_LOGGING = 435,
        TOKEN_SUB_CONFIG_CONTROL = 436,
        TOKEN_STRING = 437,
        TOKEN_INTEGER = 438,
        TOKEN_FLOAT = 439,
        TOKEN_BOOLEAN = 440
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Move or copy constructor.
      basic_symbol (YY_RVREF (basic_symbol) other);


      /// Constructor for valueless symbols, and symbols from each type.
      basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ElementPtr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (bool) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (double) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (int64_t) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l);


      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
<<<<<<< HEAD
<<<<<<< HEAD
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.template destroy< ElementPtr > ();
        break;

      case 185: // "boolean"
        value.template destroy< bool > ();
        break;

      case 184: // "floating point"
        value.template destroy< double > ();
        break;

      case 183: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 182: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }
=======
      void clear ();
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
      void clear ();
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if !defined __cplusplus || __cplusplus < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
<<<<<<< HEAD
<<<<<<< HEAD
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_COMMA || tok == token::TOKEN_COLON || tok == token::TOKEN_LSQUARE_BRACKET || tok == token::TOKEN_RSQUARE_BRACKET || tok == token::TOKEN_LCURLY_BRACKET || tok == token::TOKEN_RCURLY_BRACKET || tok == token::TOKEN_NULL_TYPE || tok == token::TOKEN_DHCP6 || tok == token::TOKEN_DATA_DIRECTORY || tok == token::TOKEN_CONFIG_CONTROL || tok == token::TOKEN_CONFIG_DATABASES || tok == token::TOKEN_CONFIG_FETCH_WAIT_TIME || tok == token::TOKEN_INTERFACES_CONFIG || tok == token::TOKEN_INTERFACES || tok == token::TOKEN_RE_DETECT || tok == token::TOKEN_LEASE_DATABASE || tok == token::TOKEN_HOSTS_DATABASE || tok == token::TOKEN_HOSTS_DATABASES || tok == token::TOKEN_TYPE || tok == token::TOKEN_MEMFILE || tok == token::TOKEN_MYSQL || tok == token::TOKEN_POSTGRESQL || tok == token::TOKEN_CQL || tok == token::TOKEN_USER || tok == token::TOKEN_PASSWORD || tok == token::TOKEN_HOST || tok == token::TOKEN_PORT || tok == token::TOKEN_PERSIST || tok == token::TOKEN_LFC_INTERVAL || tok == token::TOKEN_READONLY || tok == token::TOKEN_CONNECT_TIMEOUT || tok == token::TOKEN_CONTACT_POINTS || tok == token::TOKEN_MAX_RECONNECT_TRIES || tok == token::TOKEN_RECONNECT_WAIT_TIME || tok == token::TOKEN_KEYSPACE || tok == token::TOKEN_CONSISTENCY || tok == token::TOKEN_SERIAL_CONSISTENCY || tok == token::TOKEN_REQUEST_TIMEOUT || tok == token::TOKEN_TCP_KEEPALIVE || tok == token::TOKEN_TCP_NODELAY || tok == token::TOKEN_PREFERRED_LIFETIME || tok == token::TOKEN_MIN_PREFERRED_LIFETIME || tok == token::TOKEN_MAX_PREFERRED_LIFETIME || tok == token::TOKEN_VALID_LIFETIME || tok == token::TOKEN_MIN_VALID_LIFETIME || tok == token::TOKEN_MAX_VALID_LIFETIME || tok == token::TOKEN_RENEW_TIMER || tok == token::TOKEN_REBIND_TIMER || tok == token::TOKEN_CALCULATE_TEE_TIMES || tok == token::TOKEN_T1_PERCENT || tok == token::TOKEN_T2_PERCENT || tok == token::TOKEN_DECLINE_PROBATION_PERIOD || tok == token::TOKEN_SERVER_TAG || tok == token::TOKEN_SUBNET6 || tok == token::TOKEN_OPTION_DEF || tok == token::TOKEN_OPTION_DATA || tok == token::TOKEN_NAME || tok == token::TOKEN_DATA || tok == token::TOKEN_CODE || tok == token::TOKEN_SPACE || tok == token::TOKEN_CSV_FORMAT || tok == token::TOKEN_ALWAYS_SEND || tok == token::TOKEN_RECORD_TYPES || tok == token::TOKEN_ENCAPSULATE || tok == token::TOKEN_ARRAY || tok == token::TOKEN_POOLS || tok == token::TOKEN_POOL || tok == token::TOKEN_PD_POOLS || tok == token::TOKEN_PREFIX || tok == token::TOKEN_PREFIX_LEN || tok == token::TOKEN_EXCLUDED_PREFIX || tok == token::TOKEN_EXCLUDED_PREFIX_LEN || tok == token::TOKEN_DELEGATED_LEN || tok == token::TOKEN_USER_CONTEXT || tok == token::TOKEN_COMMENT || tok == token::TOKEN_SUBNET || tok == token::TOKEN_INTERFACE || tok == token::TOKEN_INTERFACE_ID || tok == token::TOKEN_ID || tok == token::TOKEN_RAPID_COMMIT || tok == token::TOKEN_RESERVATION_MODE || tok == token::TOKEN_DISABLED || tok == token::TOKEN_OUT_OF_POOL || tok == token::TOKEN_GLOBAL || tok == token::TOKEN_ALL || tok == token::TOKEN_SHARED_NETWORKS || tok == token::TOKEN_MAC_SOURCES || tok == token::TOKEN_RELAY_SUPPLIED_OPTIONS || tok == token::TOKEN_HOST_RESERVATION_IDENTIFIERS || tok == token::TOKEN_SANITY_CHECKS || tok == token::TOKEN_LEASE_CHECKS || tok == token::TOKEN_CLIENT_CLASSES || tok == token::TOKEN_REQUIRE_CLIENT_CLASSES || tok == token::TOKEN_TEST || tok == token::TOKEN_ONLY_IF_REQUIRED || tok == token::TOKEN_CLIENT_CLASS || tok == token::TOKEN_RESERVATIONS || tok == token::TOKEN_IP_ADDRESSES || tok == token::TOKEN_PREFIXES || tok == token::TOKEN_DUID || tok == token::TOKEN_HW_ADDRESS || tok == token::TOKEN_HOSTNAME || tok == token::TOKEN_FLEX_ID || tok == token::TOKEN_RELAY || tok == token::TOKEN_IP_ADDRESS || tok == token::TOKEN_HOOKS_LIBRARIES || tok == token::TOKEN_LIBRARY || tok == token::TOKEN_PARAMETERS || tok == token::TOKEN_EXPIRED_LEASES_PROCESSING || tok == token::TOKEN_RECLAIM_TIMER_WAIT_TIME || tok == token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME || tok == token::TOKEN_HOLD_RECLAIMED_TIME || tok == token::TOKEN_MAX_RECLAIM_LEASES || tok == token::TOKEN_MAX_RECLAIM_TIME || tok == token::TOKEN_UNWARNED_RECLAIM_CYCLES || tok == token::TOKEN_SERVER_ID || tok == token::TOKEN_LLT || tok == token::TOKEN_EN || tok == token::TOKEN_LL || tok == token::TOKEN_IDENTIFIER || tok == token::TOKEN_HTYPE || tok == token::TOKEN_TIME || tok == token::TOKEN_ENTERPRISE_ID || tok == token::TOKEN_DHCP4O6_PORT || tok == token::TOKEN_CONTROL_SOCKET || tok == token::TOKEN_SOCKET_TYPE || tok == token::TOKEN_SOCKET_NAME || tok == token::TOKEN_DHCP_QUEUE_CONTROL || tok == token::TOKEN_DHCP_DDNS || tok == token::TOKEN_ENABLE_UPDATES || tok == token::TOKEN_QUALIFYING_SUFFIX || tok == token::TOKEN_SERVER_IP || tok == token::TOKEN_SERVER_PORT || tok == token::TOKEN_SENDER_IP || tok == token::TOKEN_SENDER_PORT || tok == token::TOKEN_MAX_QUEUE_SIZE || tok == token::TOKEN_NCR_PROTOCOL || tok == token::TOKEN_NCR_FORMAT || tok == token::TOKEN_OVERRIDE_NO_UPDATE || tok == token::TOKEN_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_REPLACE_CLIENT_NAME || tok == token::TOKEN_GENERATED_PREFIX || tok == token::TOKEN_UDP || tok == token::TOKEN_TCP || tok == token::TOKEN_JSON || tok == token::TOKEN_WHEN_PRESENT || tok == token::TOKEN_NEVER || tok == token::TOKEN_ALWAYS || tok == token::TOKEN_WHEN_NOT_PRESENT || tok == token::TOKEN_HOSTNAME_CHAR_SET || tok == token::TOKEN_HOSTNAME_CHAR_REPLACEMENT || tok == token::TOKEN_LOGGING || tok == token::TOKEN_LOGGERS || tok == token::TOKEN_OUTPUT_OPTIONS || tok == token::TOKEN_OUTPUT || tok == token::TOKEN_DEBUGLEVEL || tok == token::TOKEN_SEVERITY || tok == token::TOKEN_FLUSH || tok == token::TOKEN_MAXSIZE || tok == token::TOKEN_MAXVER || tok == token::TOKEN_PATTERN || tok == token::TOKEN_DHCP4 || tok == token::TOKEN_DHCPDDNS || tok == token::TOKEN_CONTROL_AGENT || tok == token::TOKEN_TOPLEVEL_JSON || tok == token::TOKEN_TOPLEVEL_DHCP6 || tok == token::TOKEN_SUB_DHCP6 || tok == token::TOKEN_SUB_INTERFACES6 || tok == token::TOKEN_SUB_SUBNET6 || tok == token::TOKEN_SUB_POOL6 || tok == token::TOKEN_SUB_PD_POOL || tok == token::TOKEN_SUB_RESERVATION || tok == token::TOKEN_SUB_OPTION_DEFS || tok == token::TOKEN_SUB_OPTION_DEF || tok == token::TOKEN_SUB_OPTION_DATA || tok == token::TOKEN_SUB_HOOKS_LIBRARY || tok == token::TOKEN_SUB_DHCP_DDNS || tok == token::TOKEN_SUB_LOGGING || tok == token::TOKEN_SUB_CONFIG_CONTROL);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YYASSERT (tok == token::TOKEN_END || tok == token::TOKEN_COMMA || tok == token::TOKEN_COLON || tok == token::TOKEN_LSQUARE_BRACKET || tok == token::TOKEN_RSQUARE_BRACKET || tok == token::TOKEN_LCURLY_BRACKET || tok == token::TOKEN_RCURLY_BRACKET || tok == token::TOKEN_NULL_TYPE || tok == token::TOKEN_DHCP6 || tok == token::TOKEN_DATA_DIRECTORY || tok == token::TOKEN_CONFIG_CONTROL || tok == token::TOKEN_CONFIG_DATABASES || tok == token::TOKEN_CONFIG_FETCH_WAIT_TIME || tok == token::TOKEN_INTERFACES_CONFIG || tok == token::TOKEN_INTERFACES || tok == token::TOKEN_RE_DETECT || tok == token::TOKEN_LEASE_DATABASE || tok == token::TOKEN_HOSTS_DATABASE || tok == token::TOKEN_HOSTS_DATABASES || tok == token::TOKEN_TYPE || tok == token::TOKEN_MEMFILE || tok == token::TOKEN_MYSQL || tok == token::TOKEN_POSTGRESQL || tok == token::TOKEN_CQL || tok == token::TOKEN_USER || tok == token::TOKEN_PASSWORD || tok == token::TOKEN_HOST || tok == token::TOKEN_PORT || tok == token::TOKEN_PERSIST || tok == token::TOKEN_LFC_INTERVAL || tok == token::TOKEN_READONLY || tok == token::TOKEN_CONNECT_TIMEOUT || tok == token::TOKEN_CONTACT_POINTS || tok == token::TOKEN_MAX_RECONNECT_TRIES || tok == token::TOKEN_RECONNECT_WAIT_TIME || tok == token::TOKEN_KEYSPACE || tok == token::TOKEN_CONSISTENCY || tok == token::TOKEN_SERIAL_CONSISTENCY || tok == token::TOKEN_REQUEST_TIMEOUT || tok == token::TOKEN_TCP_KEEPALIVE || tok == token::TOKEN_TCP_NODELAY || tok == token::TOKEN_PREFERRED_LIFETIME || tok == token::TOKEN_MIN_PREFERRED_LIFETIME || tok == token::TOKEN_MAX_PREFERRED_LIFETIME || tok == token::TOKEN_VALID_LIFETIME || tok == token::TOKEN_MIN_VALID_LIFETIME || tok == token::TOKEN_MAX_VALID_LIFETIME || tok == token::TOKEN_RENEW_TIMER || tok == token::TOKEN_REBIND_TIMER || tok == token::TOKEN_CALCULATE_TEE_TIMES || tok == token::TOKEN_T1_PERCENT || tok == token::TOKEN_T2_PERCENT || tok == token::TOKEN_DECLINE_PROBATION_PERIOD || tok == token::TOKEN_SERVER_TAG || tok == token::TOKEN_SUBNET6 || tok == token::TOKEN_OPTION_DEF || tok == token::TOKEN_OPTION_DATA || tok == token::TOKEN_NAME || tok == token::TOKEN_DATA || tok == token::TOKEN_CODE || tok == token::TOKEN_SPACE || tok == token::TOKEN_CSV_FORMAT || tok == token::TOKEN_ALWAYS_SEND || tok == token::TOKEN_RECORD_TYPES || tok == token::TOKEN_ENCAPSULATE || tok == token::TOKEN_ARRAY || tok == token::TOKEN_POOLS || tok == token::TOKEN_POOL || tok == token::TOKEN_PD_POOLS || tok == token::TOKEN_PREFIX || tok == token::TOKEN_PREFIX_LEN || tok == token::TOKEN_EXCLUDED_PREFIX || tok == token::TOKEN_EXCLUDED_PREFIX_LEN || tok == token::TOKEN_DELEGATED_LEN || tok == token::TOKEN_USER_CONTEXT || tok == token::TOKEN_COMMENT || tok == token::TOKEN_SUBNET || tok == token::TOKEN_INTERFACE || tok == token::TOKEN_INTERFACE_ID || tok == token::TOKEN_ID || tok == token::TOKEN_RAPID_COMMIT || tok == token::TOKEN_RESERVATION_MODE || tok == token::TOKEN_DISABLED || tok == token::TOKEN_OUT_OF_POOL || tok == token::TOKEN_GLOBAL || tok == token::TOKEN_ALL || tok == token::TOKEN_SHARED_NETWORKS || tok == token::TOKEN_MAC_SOURCES || tok == token::TOKEN_RELAY_SUPPLIED_OPTIONS || tok == token::TOKEN_HOST_RESERVATION_IDENTIFIERS || tok == token::TOKEN_SANITY_CHECKS || tok == token::TOKEN_LEASE_CHECKS || tok == token::TOKEN_CLIENT_CLASSES || tok == token::TOKEN_REQUIRE_CLIENT_CLASSES || tok == token::TOKEN_TEST || tok == token::TOKEN_ONLY_IF_REQUIRED || tok == token::TOKEN_CLIENT_CLASS || tok == token::TOKEN_RESERVATIONS || tok == token::TOKEN_IP_ADDRESSES || tok == token::TOKEN_PREFIXES || tok == token::TOKEN_DUID || tok == token::TOKEN_HW_ADDRESS || tok == token::TOKEN_HOSTNAME || tok == token::TOKEN_FLEX_ID || tok == token::TOKEN_RELAY || tok == token::TOKEN_IP_ADDRESS || tok == token::TOKEN_HOOKS_LIBRARIES || tok == token::TOKEN_LIBRARY || tok == token::TOKEN_PARAMETERS || tok == token::TOKEN_EXPIRED_LEASES_PROCESSING || tok == token::TOKEN_RECLAIM_TIMER_WAIT_TIME || tok == token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME || tok == token::TOKEN_HOLD_RECLAIMED_TIME || tok == token::TOKEN_MAX_RECLAIM_LEASES || tok == token::TOKEN_MAX_RECLAIM_TIME || tok == token::TOKEN_UNWARNED_RECLAIM_CYCLES || tok == token::TOKEN_SERVER_ID || tok == token::TOKEN_LLT || tok == token::TOKEN_EN || tok == token::TOKEN_LL || tok == token::TOKEN_IDENTIFIER || tok == token::TOKEN_HTYPE || tok == token::TOKEN_TIME || tok == token::TOKEN_ENTERPRISE_ID || tok == token::TOKEN_DHCP4O6_PORT || tok == token::TOKEN_CONTROL_SOCKET || tok == token::TOKEN_SOCKET_TYPE || tok == token::TOKEN_SOCKET_NAME || tok == token::TOKEN_DHCP_QUEUE_CONTROL || tok == token::TOKEN_DHCP_DDNS || tok == token::TOKEN_ENABLE_UPDATES || tok == token::TOKEN_QUALIFYING_SUFFIX || tok == token::TOKEN_SERVER_IP || tok == token::TOKEN_SERVER_PORT || tok == token::TOKEN_SENDER_IP || tok == token::TOKEN_SENDER_PORT || tok == token::TOKEN_MAX_QUEUE_SIZE || tok == token::TOKEN_NCR_PROTOCOL || tok == token::TOKEN_NCR_FORMAT || tok == token::TOKEN_OVERRIDE_NO_UPDATE || tok == token::TOKEN_OVERRIDE_CLIENT_UPDATE || tok == token::TOKEN_REPLACE_CLIENT_NAME || tok == token::TOKEN_GENERATED_PREFIX || tok == token::TOKEN_UDP || tok == token::TOKEN_TCP || tok == token::TOKEN_JSON || tok == token::TOKEN_WHEN_PRESENT || tok == token::TOKEN_NEVER || tok == token::TOKEN_ALWAYS || tok == token::TOKEN_WHEN_NOT_PRESENT || tok == token::TOKEN_HOSTNAME_CHAR_SET || tok == token::TOKEN_HOSTNAME_CHAR_REPLACEMENT || tok == token::TOKEN_LOGGING || tok == token::TOKEN_LOGGERS || tok == token::TOKEN_OUTPUT_OPTIONS || tok == token::TOKEN_OUTPUT || tok == token::TOKEN_DEBUGLEVEL || tok == token::TOKEN_SEVERITY || tok == token::TOKEN_FLUSH || tok == token::TOKEN_MAXSIZE || tok == token::TOKEN_MAXVER || tok == token::TOKEN_PATTERN || tok == token::TOKEN_DHCP4 || tok == token::TOKEN_DHCPDDNS || tok == token::TOKEN_CONTROL_AGENT || tok == token::TOKEN_TOPLEVEL_JSON || tok == token::TOKEN_TOPLEVEL_DHCP6 || tok == token::TOKEN_SUB_DHCP6 || tok == token::TOKEN_SUB_INTERFACES6 || tok == token::TOKEN_SUB_SUBNET6 || tok == token::TOKEN_SUB_POOL6 || tok == token::TOKEN_SUB_PD_POOL || tok == token::TOKEN_SUB_RESERVATION || tok == token::TOKEN_SUB_OPTION_DEFS || tok == token::TOKEN_SUB_OPTION_DEF || tok == token::TOKEN_SUB_OPTION_DATA || tok == token::TOKEN_SUB_HOOKS_LIBRARY || tok == token::TOKEN_SUB_DHCP_DDNS || tok == token::TOKEN_SUB_LOGGING || tok == token::TOKEN_SUB_CONFIG_CONTROL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_BOOLEAN);
      }
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_BOOLEAN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_FLOAT);
      }
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_INTEGER);
      }
#else
      symbol_type (int tok, const int64_t& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_INTEGER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::TOKEN_STRING);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::TOKEN_STRING);
      }
#endif
    };
=======
    typedef basic_symbol<by_type> symbol_type;
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
    typedef basic_symbol<by_type> symbol_type;
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

    /// Build a parser object.
    Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg);
    virtual ~Dhcp6Parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if PARSER6_DEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

<<<<<<< HEAD
<<<<<<< HEAD
    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOKEN_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOKEN_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOKEN_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOKEN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOKEN_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSQUARE_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_LSQUARE_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LSQUARE_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_LSQUARE_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSQUARE_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_RSQUARE_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RSQUARE_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RSQUARE_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCURLY_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_LCURLY_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LCURLY_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_LCURLY_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCURLY_BRACKET (location_type l)
      {
        return symbol_type (token::TOKEN_RCURLY_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RCURLY_BRACKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RCURLY_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NULL_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_NULL_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_NULL_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_NULL_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DATA_DIRECTORY (location_type l)
      {
        return symbol_type (token::TOKEN_DATA_DIRECTORY, std::move (l));
      }
#else
      static
      symbol_type
      make_DATA_DIRECTORY (const location_type& l)
      {
        return symbol_type (token::TOKEN_DATA_DIRECTORY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_CONTROL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_DATABASES (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_DATABASES, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_DATABASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_DATABASES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONFIG_FETCH_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_CONFIG_FETCH_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACES_CONFIG (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACES_CONFIG, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACES_CONFIG (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACES_CONFIG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACES (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACES, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACES (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RE_DETECT (location_type l)
      {
        return symbol_type (token::TOKEN_RE_DETECT, std::move (l));
      }
#else
      static
      symbol_type
      make_RE_DETECT (const location_type& l)
      {
        return symbol_type (token::TOKEN_RE_DETECT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEASE_DATABASE (location_type l)
      {
        return symbol_type (token::TOKEN_LEASE_DATABASE, std::move (l));
      }
#else
      static
      symbol_type
      make_LEASE_DATABASE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEASE_DATABASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTS_DATABASE (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASE, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTS_DATABASE (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTS_DATABASES (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASES, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTS_DATABASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTS_DATABASES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MEMFILE (location_type l)
      {
        return symbol_type (token::TOKEN_MEMFILE, std::move (l));
      }
#else
      static
      symbol_type
      make_MEMFILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MEMFILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MYSQL (location_type l)
      {
        return symbol_type (token::TOKEN_MYSQL, std::move (l));
      }
#else
      static
      symbol_type
      make_MYSQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_MYSQL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POSTGRESQL (location_type l)
      {
        return symbol_type (token::TOKEN_POSTGRESQL, std::move (l));
      }
#else
      static
      symbol_type
      make_POSTGRESQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_POSTGRESQL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CQL (location_type l)
      {
        return symbol_type (token::TOKEN_CQL, std::move (l));
      }
#else
      static
      symbol_type
      make_CQL (const location_type& l)
      {
        return symbol_type (token::TOKEN_CQL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER (location_type l)
      {
        return symbol_type (token::TOKEN_USER, std::move (l));
      }
#else
      static
      symbol_type
      make_USER (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PASSWORD (location_type l)
      {
        return symbol_type (token::TOKEN_PASSWORD, std::move (l));
      }
#else
      static
      symbol_type
      make_PASSWORD (const location_type& l)
      {
        return symbol_type (token::TOKEN_PASSWORD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOST (location_type l)
      {
        return symbol_type (token::TOKEN_HOST, std::move (l));
      }
#else
      static
      symbol_type
      make_HOST (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERSIST (location_type l)
      {
        return symbol_type (token::TOKEN_PERSIST, std::move (l));
      }
#else
      static
      symbol_type
      make_PERSIST (const location_type& l)
      {
        return symbol_type (token::TOKEN_PERSIST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LFC_INTERVAL (location_type l)
      {
        return symbol_type (token::TOKEN_LFC_INTERVAL, std::move (l));
      }
#else
      static
      symbol_type
      make_LFC_INTERVAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_LFC_INTERVAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READONLY (location_type l)
      {
        return symbol_type (token::TOKEN_READONLY, std::move (l));
      }
#else
      static
      symbol_type
      make_READONLY (const location_type& l)
      {
        return symbol_type (token::TOKEN_READONLY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONNECT_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_CONNECT_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONNECT_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONNECT_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTACT_POINTS (location_type l)
      {
        return symbol_type (token::TOKEN_CONTACT_POINTS, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTACT_POINTS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTACT_POINTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECONNECT_TRIES (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECONNECT_TRIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECONNECT_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_RECONNECT_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYSPACE (location_type l)
      {
        return symbol_type (token::TOKEN_KEYSPACE, std::move (l));
      }
#else
      static
      symbol_type
      make_KEYSPACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_KEYSPACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONSISTENCY (location_type l)
      {
        return symbol_type (token::TOKEN_CONSISTENCY, std::move (l));
      }
#else
      static
      symbol_type
      make_CONSISTENCY (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONSISTENCY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERIAL_CONSISTENCY (location_type l)
      {
        return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, std::move (l));
      }
#else
      static
      symbol_type
      make_SERIAL_CONSISTENCY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUEST_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_REQUEST_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_REQUEST_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_REQUEST_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_KEEPALIVE (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_KEEPALIVE, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_KEEPALIVE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_KEEPALIVE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_NODELAY (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_NODELAY, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_NODELAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_NODELAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MIN_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MIN_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_PREFERRED_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_PREFERRED_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MIN_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MIN_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_VALID_LIFETIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_VALID_LIFETIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RENEW_TIMER (location_type l)
      {
        return symbol_type (token::TOKEN_RENEW_TIMER, std::move (l));
      }
#else
      static
      symbol_type
      make_RENEW_TIMER (const location_type& l)
      {
        return symbol_type (token::TOKEN_RENEW_TIMER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REBIND_TIMER (location_type l)
      {
        return symbol_type (token::TOKEN_REBIND_TIMER, std::move (l));
      }
#else
      static
      symbol_type
      make_REBIND_TIMER (const location_type& l)
      {
        return symbol_type (token::TOKEN_REBIND_TIMER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CALCULATE_TEE_TIMES (location_type l)
      {
        return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, std::move (l));
      }
#else
      static
      symbol_type
      make_CALCULATE_TEE_TIMES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T1_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_T1_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_T1_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_T1_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T2_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_T2_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_T2_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_T2_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECLINE_PROBATION_PERIOD (location_type l)
      {
        return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, std::move (l));
      }
#else
      static
      symbol_type
      make_DECLINE_PROBATION_PERIOD (const location_type& l)
      {
        return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_TAG (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_TAG, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_TAG (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_TAG, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION_DEF (location_type l)
      {
        return symbol_type (token::TOKEN_OPTION_DEF, std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION_DEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION_DEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPTION_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_OPTION_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_OPTION_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_OPTION_DATA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_DATA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CODE (location_type l)
      {
        return symbol_type (token::TOKEN_CODE, std::move (l));
      }
#else
      static
      symbol_type
      make_CODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SPACE (location_type l)
      {
        return symbol_type (token::TOKEN_SPACE, std::move (l));
      }
#else
      static
      symbol_type
      make_SPACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SPACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CSV_FORMAT (location_type l)
      {
        return symbol_type (token::TOKEN_CSV_FORMAT, std::move (l));
      }
#else
      static
      symbol_type
      make_CSV_FORMAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CSV_FORMAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALWAYS_SEND (location_type l)
      {
        return symbol_type (token::TOKEN_ALWAYS_SEND, std::move (l));
      }
#else
      static
      symbol_type
      make_ALWAYS_SEND (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALWAYS_SEND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECORD_TYPES (location_type l)
      {
        return symbol_type (token::TOKEN_RECORD_TYPES, std::move (l));
      }
#else
      static
      symbol_type
      make_RECORD_TYPES (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECORD_TYPES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENCAPSULATE (location_type l)
      {
        return symbol_type (token::TOKEN_ENCAPSULATE, std::move (l));
      }
#else
      static
      symbol_type
      make_ENCAPSULATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENCAPSULATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARRAY (location_type l)
      {
        return symbol_type (token::TOKEN_ARRAY, std::move (l));
      }
#else
      static
      symbol_type
      make_ARRAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_ARRAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POOLS (location_type l)
      {
        return symbol_type (token::TOKEN_POOLS, std::move (l));
      }
#else
      static
      symbol_type
      make_POOLS (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOLS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PD_POOLS (location_type l)
      {
        return symbol_type (token::TOKEN_PD_POOLS, std::move (l));
      }
#else
      static
      symbol_type
      make_PD_POOLS (const location_type& l)
      {
        return symbol_type (token::TOKEN_PD_POOLS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIX_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIX_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIX_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIX_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLUDED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLUDED_PREFIX_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDED_PREFIX_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DELEGATED_LEN (location_type l)
      {
        return symbol_type (token::TOKEN_DELEGATED_LEN, std::move (l));
      }
#else
      static
      symbol_type
      make_DELEGATED_LEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DELEGATED_LEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER_CONTEXT (location_type l)
      {
        return symbol_type (token::TOKEN_USER_CONTEXT, std::move (l));
      }
#else
      static
      symbol_type
      make_USER_CONTEXT (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER_CONTEXT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMENT (location_type l)
      {
        return symbol_type (token::TOKEN_COMMENT, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTERFACE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_INTERFACE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_INTERFACE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_INTERFACE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RAPID_COMMIT (location_type l)
      {
        return symbol_type (token::TOKEN_RAPID_COMMIT, std::move (l));
      }
#else
      static
      symbol_type
      make_RAPID_COMMIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_RAPID_COMMIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATION_MODE (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATION_MODE, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATION_MODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATION_MODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DISABLED (location_type l)
      {
        return symbol_type (token::TOKEN_DISABLED, std::move (l));
      }
#else
      static
      symbol_type
      make_DISABLED (const location_type& l)
      {
        return symbol_type (token::TOKEN_DISABLED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUT_OF_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_OUT_OF_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_OUT_OF_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUT_OF_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GLOBAL (location_type l)
      {
        return symbol_type (token::TOKEN_GLOBAL, std::move (l));
      }
#else
      static
      symbol_type
      make_GLOBAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_GLOBAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALL (location_type l)
      {
        return symbol_type (token::TOKEN_ALL, std::move (l));
      }
#else
      static
      symbol_type
      make_ALL (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SHARED_NETWORKS (location_type l)
      {
        return symbol_type (token::TOKEN_SHARED_NETWORKS, std::move (l));
      }
#else
      static
      symbol_type
      make_SHARED_NETWORKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SHARED_NETWORKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAC_SOURCES (location_type l)
      {
        return symbol_type (token::TOKEN_MAC_SOURCES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAC_SOURCES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAC_SOURCES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY_SUPPLIED_OPTIONS (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY_SUPPLIED_OPTIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOST_RESERVATION_IDENTIFIERS (location_type l)
      {
        return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, std::move (l));
      }
#else
      static
      symbol_type
      make_HOST_RESERVATION_IDENTIFIERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SANITY_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_SANITY_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_SANITY_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SANITY_CHECKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEASE_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_LEASE_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_LEASE_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEASE_CHECKS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_CLASSES (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASSES, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_CLASSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REQUIRE_CLIENT_CLASSES (location_type l)
      {
        return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, std::move (l));
      }
#else
      static
      symbol_type
      make_REQUIRE_CLIENT_CLASSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TEST (location_type l)
      {
        return symbol_type (token::TOKEN_TEST, std::move (l));
      }
#else
      static
      symbol_type
      make_TEST (const location_type& l)
      {
        return symbol_type (token::TOKEN_TEST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ONLY_IF_REQUIRED (location_type l)
      {
        return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, std::move (l));
      }
#else
      static
      symbol_type
      make_ONLY_IF_REQUIRED (const location_type& l)
      {
        return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_CLASS (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_CLASS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_CLASS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_ADDRESSES (location_type l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESSES, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_ADDRESSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESSES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PREFIXES (location_type l)
      {
        return symbol_type (token::TOKEN_PREFIXES, std::move (l));
      }
#else
      static
      symbol_type
      make_PREFIXES (const location_type& l)
      {
        return symbol_type (token::TOKEN_PREFIXES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DUID (location_type l)
      {
        return symbol_type (token::TOKEN_DUID, std::move (l));
      }
#else
      static
      symbol_type
      make_DUID (const location_type& l)
      {
        return symbol_type (token::TOKEN_DUID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HW_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_HW_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_HW_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HW_ADDRESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLEX_ID (location_type l)
      {
        return symbol_type (token::TOKEN_FLEX_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_FLEX_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLEX_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RELAY (location_type l)
      {
        return symbol_type (token::TOKEN_RELAY, std::move (l));
      }
#else
      static
      symbol_type
      make_RELAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_RELAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_ADDRESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOOKS_LIBRARIES (location_type l)
      {
        return symbol_type (token::TOKEN_HOOKS_LIBRARIES, std::move (l));
      }
#else
      static
      symbol_type
      make_HOOKS_LIBRARIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOOKS_LIBRARIES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LIBRARY (location_type l)
      {
        return symbol_type (token::TOKEN_LIBRARY, std::move (l));
      }
#else
      static
      symbol_type
      make_LIBRARY (const location_type& l)
      {
        return symbol_type (token::TOKEN_LIBRARY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARAMETERS (location_type l)
      {
        return symbol_type (token::TOKEN_PARAMETERS, std::move (l));
      }
#else
      static
      symbol_type
      make_PARAMETERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARAMETERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXPIRED_LEASES_PROCESSING (location_type l)
      {
        return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, std::move (l));
      }
#else
      static
      symbol_type
      make_EXPIRED_LEASES_PROCESSING (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECLAIM_TIMER_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_RECLAIM_TIMER_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLD_RECLAIMED_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_HOLD_RECLAIMED_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECLAIM_LEASES (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECLAIM_LEASES (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_RECLAIM_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_RECLAIM_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNWARNED_RECLAIM_CYCLES (location_type l)
      {
        return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, std::move (l));
      }
#else
      static
      symbol_type
      make_UNWARNED_RECLAIM_CYCLES (const location_type& l)
      {
        return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_ID (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LLT (location_type l)
      {
        return symbol_type (token::TOKEN_LLT, std::move (l));
      }
#else
      static
      symbol_type
      make_LLT (const location_type& l)
      {
        return symbol_type (token::TOKEN_LLT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EN (location_type l)
      {
        return symbol_type (token::TOKEN_EN, std::move (l));
      }
#else
      static
      symbol_type
      make_EN (const location_type& l)
      {
        return symbol_type (token::TOKEN_EN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LL (location_type l)
      {
        return symbol_type (token::TOKEN_LL, std::move (l));
      }
#else
      static
      symbol_type
      make_LL (const location_type& l)
      {
        return symbol_type (token::TOKEN_LL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (location_type l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const location_type& l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTYPE (location_type l)
      {
        return symbol_type (token::TOKEN_HTYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_HTYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENTERPRISE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ENTERPRISE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENTERPRISE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP4O6_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP4O6_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP4O6_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP4O6_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTROL_SOCKET (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKET, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_SOCKET (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP_QUEUE_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_QUEUE_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENABLE_UPDATES (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_UPDATES, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_UPDATES (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_UPDATES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QUALIFYING_SUFFIX (location_type l)
      {
        return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_QUALIFYING_SUFFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_IP (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_IP, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_IP (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_IP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SENDER_IP (location_type l)
      {
        return symbol_type (token::TOKEN_SENDER_IP, std::move (l));
      }
#else
      static
      symbol_type
      make_SENDER_IP (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDER_IP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SENDER_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SENDER_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SENDER_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDER_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_QUEUE_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_QUEUE_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NCR_PROTOCOL (location_type l)
      {
        return symbol_type (token::TOKEN_NCR_PROTOCOL, std::move (l));
      }
#else
      static
      symbol_type
      make_NCR_PROTOCOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_NCR_PROTOCOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NCR_FORMAT (location_type l)
      {
        return symbol_type (token::TOKEN_NCR_FORMAT, std::move (l));
      }
#else
      static
      symbol_type
      make_NCR_FORMAT (const location_type& l)
      {
        return symbol_type (token::TOKEN_NCR_FORMAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OVERRIDE_NO_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_OVERRIDE_NO_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OVERRIDE_CLIENT_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_OVERRIDE_CLIENT_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REPLACE_CLIENT_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_REPLACE_CLIENT_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GENERATED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_GENERATED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_GENERATED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_GENERATED_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UDP (location_type l)
      {
        return symbol_type (token::TOKEN_UDP, std::move (l));
      }
#else
      static
      symbol_type
      make_UDP (const location_type& l)
      {
        return symbol_type (token::TOKEN_UDP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP (location_type l)
      {
        return symbol_type (token::TOKEN_TCP, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_JSON (location_type l)
      {
        return symbol_type (token::TOKEN_JSON, std::move (l));
      }
#else
      static
      symbol_type
      make_JSON (const location_type& l)
      {
        return symbol_type (token::TOKEN_JSON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHEN_PRESENT (location_type l)
      {
        return symbol_type (token::TOKEN_WHEN_PRESENT, std::move (l));
      }
#else
      static
      symbol_type
      make_WHEN_PRESENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHEN_PRESENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEVER (location_type l)
      {
        return symbol_type (token::TOKEN_NEVER, std::move (l));
      }
#else
      static
      symbol_type
      make_NEVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALWAYS (location_type l)
      {
        return symbol_type (token::TOKEN_ALWAYS, std::move (l));
      }
#else
      static
      symbol_type
      make_ALWAYS (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALWAYS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHEN_NOT_PRESENT (location_type l)
      {
        return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, std::move (l));
      }
#else
      static
      symbol_type
      make_WHEN_NOT_PRESENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME_CHAR_SET (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME_CHAR_SET (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOSTNAME_CHAR_REPLACEMENT (location_type l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, std::move (l));
      }
#else
      static
      symbol_type
      make_HOSTNAME_CHAR_REPLACEMENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGGING (location_type l)
      {
        return symbol_type (token::TOKEN_LOGGING, std::move (l));
      }
#else
      static
      symbol_type
      make_LOGGING (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOGGING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGGERS (location_type l)
      {
        return symbol_type (token::TOKEN_LOGGERS, std::move (l));
      }
#else
      static
      symbol_type
      make_LOGGERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOGGERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUTPUT_OPTIONS (location_type l)
      {
        return symbol_type (token::TOKEN_OUTPUT_OPTIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTPUT_OPTIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTPUT_OPTIONS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUTPUT (location_type l)
      {
        return symbol_type (token::TOKEN_OUTPUT, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTPUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTPUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEBUGLEVEL (location_type l)
      {
        return symbol_type (token::TOKEN_DEBUGLEVEL, std::move (l));
      }
#else
      static
      symbol_type
      make_DEBUGLEVEL (const location_type& l)
      {
        return symbol_type (token::TOKEN_DEBUGLEVEL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEVERITY (location_type l)
      {
        return symbol_type (token::TOKEN_SEVERITY, std::move (l));
      }
#else
      static
      symbol_type
      make_SEVERITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SEVERITY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLUSH (location_type l)
      {
        return symbol_type (token::TOKEN_FLUSH, std::move (l));
      }
#else
      static
      symbol_type
      make_FLUSH (const location_type& l)
      {
        return symbol_type (token::TOKEN_FLUSH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAXSIZE (location_type l)
      {
        return symbol_type (token::TOKEN_MAXSIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_MAXSIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAXSIZE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAXVER (location_type l)
      {
        return symbol_type (token::TOKEN_MAXVER, std::move (l));
      }
#else
      static
      symbol_type
      make_MAXVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAXVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PATTERN (location_type l)
      {
        return symbol_type (token::TOKEN_PATTERN, std::move (l));
      }
#else
      static
      symbol_type
      make_PATTERN (const location_type& l)
      {
        return symbol_type (token::TOKEN_PATTERN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DHCPDDNS (location_type l)
      {
        return symbol_type (token::TOKEN_DHCPDDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCPDDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCPDDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTROL_AGENT (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_AGENT, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_AGENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_AGENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_JSON (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_JSON, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_JSON (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_JSON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOPLEVEL_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCP6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_INTERFACES6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_INTERFACES6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_SUBNET6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_SUBNET6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_POOL6 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_POOL6, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_POOL6 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_POOL6, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_PD_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_PD_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_PD_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_PD_POOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_RESERVATION (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_RESERVATION, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_RESERVATION (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_RESERVATION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DEFS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEFS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DEFS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEFS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DEF (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEF, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_OPTION_DATA (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DATA, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_OPTION_DATA (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPTION_DATA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_HOOKS_LIBRARY (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_HOOKS_LIBRARY (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCP_DDNS (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP_DDNS, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP_DDNS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP_DDNS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_LOGGING (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_LOGGING, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_LOGGING (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_LOGGING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_CONFIG_CONTROL (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_CONFIG_CONTROL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (int64_t v, location_type l)
      {
        return symbol_type (token::TOKEN_INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const int64_t& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (double v, location_type l)
      {
        return symbol_type (token::TOKEN_FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const double& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_FLOAT, v, l);
      }
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
    // Symbol constructors declarations.
    static
    symbol_type
    make_END (YY_COPY (location_type) l);
<<<<<<< HEAD

    static
    symbol_type
    make_COMMA (YY_COPY (location_type) l);

    static
    symbol_type
    make_COLON (YY_COPY (location_type) l);

    static
    symbol_type
    make_LSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_LCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_NULL_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DATA_DIRECTORY (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_DATABASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_FETCH_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACES_CONFIG (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RE_DETECT (YY_COPY (location_type) l);

    static
    symbol_type
    make_LEASE_DATABASE (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTS_DATABASE (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTS_DATABASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MEMFILE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MYSQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_POSTGRESQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_CQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_USER (YY_COPY (location_type) l);

    static
    symbol_type
    make_PASSWORD (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOST (YY_COPY (location_type) l);

    static
    symbol_type
    make_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_PERSIST (YY_COPY (location_type) l);

    static
    symbol_type
    make_LFC_INTERVAL (YY_COPY (location_type) l);

    static
    symbol_type
    make_READONLY (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONNECT_TIMEOUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTACT_POINTS (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECONNECT_TRIES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECONNECT_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_KEYSPACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONSISTENCY (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERIAL_CONSISTENCY (YY_COPY (location_type) l);

    static
    symbol_type
    make_REQUEST_TIMEOUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP_KEEPALIVE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP_NODELAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_ROW_ERRORS (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MIN_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MIN_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_RENEW_TIMER (YY_COPY (location_type) l);

    static
    symbol_type
    make_REBIND_TIMER (YY_COPY (location_type) l);

    static
    symbol_type
    make_CALCULATE_TEE_TIMES (YY_COPY (location_type) l);

    static
    symbol_type
    make_T1_PERCENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_T2_PERCENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_DECLINE_PROBATION_PERIOD (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_TAG (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUBNET6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION_DEF (YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_CODE (YY_COPY (location_type) l);

    static
    symbol_type
    make_SPACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CSV_FORMAT (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALWAYS_SEND (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECORD_TYPES (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENCAPSULATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_ARRAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_POOLS (YY_COPY (location_type) l);

    static
    symbol_type
    make_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_PD_POOLS (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIX_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXCLUDED_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXCLUDED_PREFIX_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_DELEGATED_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_USER_CONTEXT (YY_COPY (location_type) l);

    static
    symbol_type
    make_COMMENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUBNET (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACE_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_RAPID_COMMIT (YY_COPY (location_type) l);

    static
    symbol_type
    make_RESERVATION_MODE (YY_COPY (location_type) l);

    static
    symbol_type
    make_DISABLED (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUT_OF_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_GLOBAL (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SHARED_NETWORKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAC_SOURCES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY_SUPPLIED_OPTIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOST_RESERVATION_IDENTIFIERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SANITY_CHECKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_LEASE_CHECKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_CLIENT_CLASSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_REQUIRE_CLIENT_CLASSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_TEST (YY_COPY (location_type) l);

    static
    symbol_type
    make_ONLY_IF_REQUIRED (YY_COPY (location_type) l);

    static
    symbol_type
    make_CLIENT_CLASS (YY_COPY (location_type) l);

    static
    symbol_type
    make_RESERVATIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_IP_ADDRESSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIXES (YY_COPY (location_type) l);

    static
    symbol_type
    make_DUID (YY_COPY (location_type) l);

    static
    symbol_type
    make_HW_ADDRESS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLEX_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_IP_ADDRESS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOOKS_LIBRARIES (YY_COPY (location_type) l);

    static
    symbol_type
    make_LIBRARY (YY_COPY (location_type) l);

    static
    symbol_type
    make_PARAMETERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXPIRED_LEASES_PROCESSING (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECLAIM_TIMER_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOLD_RECLAIMED_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECLAIM_LEASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECLAIM_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_UNWARNED_RECLAIM_CYCLES (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_LLT (YY_COPY (location_type) l);

    static
    symbol_type
    make_EN (YY_COPY (location_type) l);

    static
    symbol_type
    make_LL (YY_COPY (location_type) l);

    static
    symbol_type
    make_IDENTIFIER (YY_COPY (location_type) l);

    static
    symbol_type
    make_HTYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENTERPRISE_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4O6_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_SOCKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP_QUEUE_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP_DDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENABLE_UPDATES (YY_COPY (location_type) l);

    static
    symbol_type
    make_QUALIFYING_SUFFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_IP (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_SENDER_IP (YY_COPY (location_type) l);

    static
    symbol_type
    make_SENDER_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_QUEUE_SIZE (YY_COPY (location_type) l);

    static
    symbol_type
    make_NCR_PROTOCOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_NCR_FORMAT (YY_COPY (location_type) l);

    static
    symbol_type
    make_OVERRIDE_NO_UPDATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_OVERRIDE_CLIENT_UPDATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_REPLACE_CLIENT_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_GENERATED_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_UDP (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP (YY_COPY (location_type) l);

    static
    symbol_type
    make_JSON (YY_COPY (location_type) l);

    static
    symbol_type
    make_WHEN_PRESENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_NEVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALWAYS (YY_COPY (location_type) l);

    static
    symbol_type
    make_WHEN_NOT_PRESENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME_CHAR_SET (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME_CHAR_REPLACEMENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGING (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT_OPTIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_DEBUGLEVEL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SEVERITY (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLUSH (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXSIZE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCPDDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_AGENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_JSON (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_INTERFACES6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_SUBNET6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_POOL6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_PD_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_RESERVATION (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DEFS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DEF (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_HOOKS_LIBRARY (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_DHCP_DDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_LOGGING (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_CONFIG_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l);



  private:
    /// This class is not copyable.
    Dhcp6Parser (const Dhcp6Parser&);
    Dhcp6Parser& operator= (const Dhcp6Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned short yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if PARSER6_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if !defined __cplusplus || __cplusplus < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1107,     ///< Last index in yytable_.
      yynnts_ = 404,  ///< Number of nonterminal symbols.
      yyfinal_ = 32, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 186  ///< Number of tokens.
    };


    // User arguments.
    isc::dhcp::Parser6Context& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  Dhcp6Parser::token_number_type
  Dhcp6Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185
    };
    const unsigned user_token_number_max_ = 440;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Dhcp6Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value ()
    , location (YY_MOVE (other.location))
  {
    switch (other.type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (other.value));
        break;

      case 185: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (other.value));
        break;

      case 184: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (other.value));
        break;

      case 183: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (other.value));
        break;

      case 182: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (other.value));
        break;

      default:
        break;
    }

  }


  // Implementation of basic_symbol constructor for each type.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l)
    : Base (t)
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ElementPtr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (bool) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (double) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (int64_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}



  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.template destroy< ElementPtr > ();
        break;

      case 185: // "boolean"
        value.template destroy< bool > ();
        break;

      case 184: // "floating point"
        value.template destroy< double > ();
        break;

      case 183: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 182: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  Dhcp6Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case 185: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case 184: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case 182: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  Dhcp6Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Dhcp6Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Dhcp6Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Dhcp6Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Dhcp6Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Dhcp6Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Dhcp6Parser::token_type
  Dhcp6Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }

  // Implementation of make_symbol for each symbol type.
  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_END (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_END, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_COMMA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_COLON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COLON, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NULL_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NULL_TYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DATA_DIRECTORY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DATA_DIRECTORY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_CONTROL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_DATABASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_DATABASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_FETCH_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACES_CONFIG (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACES_CONFIG, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RE_DETECT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RE_DETECT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LEASE_DATABASE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LEASE_DATABASE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTS_DATABASE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTS_DATABASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MEMFILE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MEMFILE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MYSQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MYSQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POSTGRESQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POSTGRESQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_USER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_USER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PASSWORD (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PASSWORD, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PORT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PERSIST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PERSIST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LFC_INTERVAL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LFC_INTERVAL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_READONLY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_READONLY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONNECT_TIMEOUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONNECT_TIMEOUT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONTACT_POINTS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTACT_POINTS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECONNECT_TRIES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECONNECT_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_KEYSPACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_KEYSPACE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONSISTENCY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONSISTENCY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERIAL_CONSISTENCY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REQUEST_TIMEOUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REQUEST_TIMEOUT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TCP_KEEPALIVE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TCP_KEEPALIVE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TCP_NODELAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TCP_NODELAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_ROW_ERRORS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_ROW_ERRORS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MIN_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MIN_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RENEW_TIMER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RENEW_TIMER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REBIND_TIMER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REBIND_TIMER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CALCULATE_TEE_TIMES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_T1_PERCENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_T1_PERCENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_T2_PERCENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_T2_PERCENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DECLINE_PROBATION_PERIOD (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_TAG (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_TAG, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUBNET6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUBNET6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OPTION_DEF (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION_DEF, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OPTION_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION_DATA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DATA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CODE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CODE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SPACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SPACE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CSV_FORMAT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CSV_FORMAT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ALWAYS_SEND (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ALWAYS_SEND, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECORD_TYPES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECORD_TYPES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ENCAPSULATE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENCAPSULATE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ARRAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ARRAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POOLS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POOLS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PD_POOLS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PD_POOLS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIX, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIX_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIX_LEN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EXCLUDED_PREFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXCLUDED_PREFIX, YY_MOVE (l));
=======

    static
    symbol_type
    make_COMMA (YY_COPY (location_type) l);

    static
    symbol_type
    make_COLON (YY_COPY (location_type) l);

    static
    symbol_type
    make_LSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RSQUARE_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_LCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_RCURLY_BRACKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_NULL_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DATA_DIRECTORY (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_DATABASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONFIG_FETCH_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACES_CONFIG (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RE_DETECT (YY_COPY (location_type) l);

    static
    symbol_type
    make_LEASE_DATABASE (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTS_DATABASE (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTS_DATABASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MEMFILE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MYSQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_POSTGRESQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_CQL (YY_COPY (location_type) l);

    static
    symbol_type
    make_USER (YY_COPY (location_type) l);

    static
    symbol_type
    make_PASSWORD (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOST (YY_COPY (location_type) l);

    static
    symbol_type
    make_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_PERSIST (YY_COPY (location_type) l);

    static
    symbol_type
    make_LFC_INTERVAL (YY_COPY (location_type) l);

    static
    symbol_type
    make_READONLY (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONNECT_TIMEOUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTACT_POINTS (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECONNECT_TRIES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECONNECT_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_KEYSPACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONSISTENCY (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERIAL_CONSISTENCY (YY_COPY (location_type) l);

    static
    symbol_type
    make_REQUEST_TIMEOUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP_KEEPALIVE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP_NODELAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_ROW_ERRORS (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MIN_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MIN_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_RENEW_TIMER (YY_COPY (location_type) l);

    static
    symbol_type
    make_REBIND_TIMER (YY_COPY (location_type) l);

    static
    symbol_type
    make_CALCULATE_TEE_TIMES (YY_COPY (location_type) l);

    static
    symbol_type
    make_T1_PERCENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_T2_PERCENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_DECLINE_PROBATION_PERIOD (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_TAG (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUBNET6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION_DEF (YY_COPY (location_type) l);

    static
    symbol_type
    make_OPTION_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_CODE (YY_COPY (location_type) l);

    static
    symbol_type
    make_SPACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CSV_FORMAT (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALWAYS_SEND (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECORD_TYPES (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENCAPSULATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_ARRAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_POOLS (YY_COPY (location_type) l);

    static
    symbol_type
    make_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_PD_POOLS (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIX_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXCLUDED_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXCLUDED_PREFIX_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_DELEGATED_LEN (YY_COPY (location_type) l);

    static
    symbol_type
    make_USER_CONTEXT (YY_COPY (location_type) l);

    static
    symbol_type
    make_COMMENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUBNET (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACE (YY_COPY (location_type) l);

    static
    symbol_type
    make_INTERFACE_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_RAPID_COMMIT (YY_COPY (location_type) l);

    static
    symbol_type
    make_RESERVATION_MODE (YY_COPY (location_type) l);

    static
    symbol_type
    make_DISABLED (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUT_OF_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_GLOBAL (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SHARED_NETWORKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAC_SOURCES (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY_SUPPLIED_OPTIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOST_RESERVATION_IDENTIFIERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SANITY_CHECKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_LEASE_CHECKS (YY_COPY (location_type) l);

    static
    symbol_type
    make_CLIENT_CLASSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_REQUIRE_CLIENT_CLASSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_TEST (YY_COPY (location_type) l);

    static
    symbol_type
    make_ONLY_IF_REQUIRED (YY_COPY (location_type) l);

    static
    symbol_type
    make_CLIENT_CLASS (YY_COPY (location_type) l);

    static
    symbol_type
    make_RESERVATIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_IP_ADDRESSES (YY_COPY (location_type) l);

    static
    symbol_type
    make_PREFIXES (YY_COPY (location_type) l);

    static
    symbol_type
    make_DUID (YY_COPY (location_type) l);

    static
    symbol_type
    make_HW_ADDRESS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLEX_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_RELAY (YY_COPY (location_type) l);

    static
    symbol_type
    make_IP_ADDRESS (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOOKS_LIBRARIES (YY_COPY (location_type) l);

    static
    symbol_type
    make_LIBRARY (YY_COPY (location_type) l);

    static
    symbol_type
    make_PARAMETERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_EXPIRED_LEASES_PROCESSING (YY_COPY (location_type) l);

    static
    symbol_type
    make_RECLAIM_TIMER_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOLD_RECLAIMED_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECLAIM_LEASES (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_RECLAIM_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_UNWARNED_RECLAIM_CYCLES (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_LLT (YY_COPY (location_type) l);

    static
    symbol_type
    make_EN (YY_COPY (location_type) l);

    static
    symbol_type
    make_LL (YY_COPY (location_type) l);

    static
    symbol_type
    make_IDENTIFIER (YY_COPY (location_type) l);

    static
    symbol_type
    make_HTYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_TIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENTERPRISE_ID (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4O6_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_SOCKET (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_SOCKET_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP_QUEUE_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP_DDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_ENABLE_UPDATES (YY_COPY (location_type) l);

    static
    symbol_type
    make_QUALIFYING_SUFFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_IP (YY_COPY (location_type) l);

    static
    symbol_type
    make_SERVER_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_SENDER_IP (YY_COPY (location_type) l);

    static
    symbol_type
    make_SENDER_PORT (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAX_QUEUE_SIZE (YY_COPY (location_type) l);

    static
    symbol_type
    make_NCR_PROTOCOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_NCR_FORMAT (YY_COPY (location_type) l);

    static
    symbol_type
    make_OVERRIDE_NO_UPDATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_OVERRIDE_CLIENT_UPDATE (YY_COPY (location_type) l);

    static
    symbol_type
    make_REPLACE_CLIENT_NAME (YY_COPY (location_type) l);

    static
    symbol_type
    make_GENERATED_PREFIX (YY_COPY (location_type) l);

    static
    symbol_type
    make_UDP (YY_COPY (location_type) l);

    static
    symbol_type
    make_TCP (YY_COPY (location_type) l);

    static
    symbol_type
    make_JSON (YY_COPY (location_type) l);

    static
    symbol_type
    make_WHEN_PRESENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_NEVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_ALWAYS (YY_COPY (location_type) l);

    static
    symbol_type
    make_WHEN_NOT_PRESENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME_CHAR_SET (YY_COPY (location_type) l);

    static
    symbol_type
    make_HOSTNAME_CHAR_REPLACEMENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGING (YY_COPY (location_type) l);

    static
    symbol_type
    make_LOGGERS (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT_OPTIONS (YY_COPY (location_type) l);

    static
    symbol_type
    make_OUTPUT (YY_COPY (location_type) l);

    static
    symbol_type
    make_DEBUGLEVEL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SEVERITY (YY_COPY (location_type) l);

    static
    symbol_type
    make_FLUSH (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXSIZE (YY_COPY (location_type) l);

    static
    symbol_type
    make_MAXVER (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCP4 (YY_COPY (location_type) l);

    static
    symbol_type
    make_DHCPDDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_CONTROL_AGENT (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_JSON (YY_COPY (location_type) l);

    static
    symbol_type
    make_TOPLEVEL_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_DHCP6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_INTERFACES6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_SUBNET6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_POOL6 (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_PD_POOL (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_RESERVATION (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DEFS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DEF (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_OPTION_DATA (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_HOOKS_LIBRARY (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_DHCP_DDNS (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_LOGGING (YY_COPY (location_type) l);

    static
    symbol_type
    make_SUB_CONFIG_CONTROL (YY_COPY (location_type) l);

    static
    symbol_type
    make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l);



  private:
    /// This class is not copyable.
    Dhcp6Parser (const Dhcp6Parser&);
    Dhcp6Parser& operator= (const Dhcp6Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned short yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned short yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if PARSER6_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if !defined __cplusplus || __cplusplus < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1107,     ///< Last index in yytable_.
      yynnts_ = 404,  ///< Number of nonterminal symbols.
      yyfinal_ = 32, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 186  ///< Number of tokens.
    };


    // User arguments.
    isc::dhcp::Parser6Context& ctx;
  };

  // Symbol number corresponding to token number t.
  inline
  Dhcp6Parser::token_number_type
  Dhcp6Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185
    };
    const unsigned user_token_number_max_ = 440;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Dhcp6Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value ()
    , location (YY_MOVE (other.location))
  {
    switch (other.type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (other.value));
        break;

      case 185: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (other.value));
        break;

      case 184: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (other.value));
        break;

      case 183: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (other.value));
        break;

      case 182: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (other.value));
        break;

      default:
        break;
    }

  }


  // Implementation of basic_symbol constructor for each type.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l)
    : Base (t)
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ElementPtr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (bool) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (double) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (int64_t) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (std::string) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}



  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.template destroy< ElementPtr > ();
        break;

      case 185: // "boolean"
        value.template destroy< bool > ();
        break;

      case 184: // "floating point"
        value.template destroy< double > ();
        break;

      case 183: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 182: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  Dhcp6Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 362: // hr_mode
      case 498: // duid_type
      case 533: // ncr_protocol_value
      case 540: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case 185: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case 184: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case 182: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  Dhcp6Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Dhcp6Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Dhcp6Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Dhcp6Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Dhcp6Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Dhcp6Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Dhcp6Parser::token_type
  Dhcp6Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }

  // Implementation of make_symbol for each symbol type.
  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_END (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_END, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_COMMA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_COLON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COLON, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RSQUARE_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RSQUARE_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RCURLY_BRACKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RCURLY_BRACKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NULL_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NULL_TYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DATA_DIRECTORY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DATA_DIRECTORY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_CONTROL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_DATABASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_DATABASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONFIG_FETCH_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONFIG_FETCH_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACES_CONFIG (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACES_CONFIG, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RE_DETECT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RE_DETECT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LEASE_DATABASE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LEASE_DATABASE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTS_DATABASE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTS_DATABASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTS_DATABASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MEMFILE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MEMFILE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MYSQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MYSQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POSTGRESQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POSTGRESQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CQL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CQL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_USER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_USER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PASSWORD (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PASSWORD, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PORT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PERSIST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PERSIST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LFC_INTERVAL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LFC_INTERVAL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_READONLY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_READONLY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONNECT_TIMEOUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONNECT_TIMEOUT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONTACT_POINTS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTACT_POINTS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECONNECT_TRIES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECONNECT_TRIES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECONNECT_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECONNECT_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_KEYSPACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_KEYSPACE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONSISTENCY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONSISTENCY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERIAL_CONSISTENCY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERIAL_CONSISTENCY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REQUEST_TIMEOUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REQUEST_TIMEOUT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TCP_KEEPALIVE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TCP_KEEPALIVE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TCP_NODELAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TCP_NODELAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_ROW_ERRORS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_ROW_ERRORS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MIN_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MIN_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MIN_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MIN_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_VALID_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RENEW_TIMER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RENEW_TIMER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REBIND_TIMER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REBIND_TIMER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CALCULATE_TEE_TIMES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CALCULATE_TEE_TIMES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_T1_PERCENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_T1_PERCENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_T2_PERCENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_T2_PERCENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DECLINE_PROBATION_PERIOD (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DECLINE_PROBATION_PERIOD, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_TAG (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_TAG, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUBNET6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUBNET6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OPTION_DEF (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION_DEF, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OPTION_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OPTION_DATA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DATA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CODE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CODE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SPACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SPACE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CSV_FORMAT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CSV_FORMAT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ALWAYS_SEND (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ALWAYS_SEND, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECORD_TYPES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECORD_TYPES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ENCAPSULATE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENCAPSULATE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ARRAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ARRAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POOLS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POOLS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_POOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PD_POOLS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PD_POOLS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIX, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIX_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIX_LEN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EXCLUDED_PREFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXCLUDED_PREFIX, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EXCLUDED_PREFIX_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DELEGATED_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DELEGATED_LEN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_USER_CONTEXT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_USER_CONTEXT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_COMMENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUBNET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUBNET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTERFACE_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACE_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RAPID_COMMIT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RAPID_COMMIT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RESERVATION_MODE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RESERVATION_MODE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DISABLED (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DISABLED, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OUT_OF_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUT_OF_POOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_GLOBAL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_GLOBAL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ALL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ALL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SHARED_NETWORKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SHARED_NETWORKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAC_SOURCES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAC_SOURCES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RELAY_SUPPLIED_OPTIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOST_RESERVATION_IDENTIFIERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SANITY_CHECKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SANITY_CHECKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LEASE_CHECKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LEASE_CHECKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CLIENT_CLASSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REQUIRE_CLIENT_CLASSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TEST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TEST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ONLY_IF_REQUIRED (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CLIENT_CLASS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RESERVATIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RESERVATIONS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_IP_ADDRESSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIXES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIXES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DUID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DUID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HW_ADDRESS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HW_ADDRESS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTNAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTNAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLEX_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLEX_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RELAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_IP_ADDRESS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOOKS_LIBRARIES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOOKS_LIBRARIES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LIBRARY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PARAMETERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PARAMETERS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EXPIRED_LEASES_PROCESSING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECLAIM_TIMER_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOLD_RECLAIMED_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECLAIM_LEASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECLAIM_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_UNWARNED_RECLAIM_CYCLES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LLT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LLT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LL, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_EXCLUDED_PREFIX_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXCLUDED_PREFIX_LEN, YY_MOVE (l));
=======
  Dhcp6Parser::make_IDENTIFIER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IDENTIFIER, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_DELEGATED_LEN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DELEGATED_LEN, YY_MOVE (l));
=======
  Dhcp6Parser::make_HTYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HTYPE, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_USER_CONTEXT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_USER_CONTEXT, YY_MOVE (l));
=======
  Dhcp6Parser::make_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TIME, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_COMMENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_COMMENT, YY_MOVE (l));
=======
  Dhcp6Parser::make_ENTERPRISE_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENTERPRISE_ID, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUBNET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUBNET, YY_MOVE (l));
=======
  Dhcp6Parser::make_DHCP4O6_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4O6_PORT, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_INTERFACE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACE, YY_MOVE (l));
=======
  Dhcp6Parser::make_CONTROL_SOCKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_SOCKET, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_INTERFACE_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTERFACE_ID, YY_MOVE (l));
=======
  Dhcp6Parser::make_SOCKET_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_TYPE, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ID, YY_MOVE (l));
=======
  Dhcp6Parser::make_SOCKET_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_NAME, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_RAPID_COMMIT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RAPID_COMMIT, YY_MOVE (l));
=======
  Dhcp6Parser::make_DHCP_QUEUE_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_RESERVATION_MODE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RESERVATION_MODE, YY_MOVE (l));
=======
  Dhcp6Parser::make_DHCP_DDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP_DDNS, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_DISABLED (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DISABLED, YY_MOVE (l));
=======
  Dhcp6Parser::make_ENABLE_UPDATES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENABLE_UPDATES, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_OUT_OF_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUT_OF_POOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_GLOBAL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_GLOBAL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ALL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ALL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SHARED_NETWORKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SHARED_NETWORKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAC_SOURCES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAC_SOURCES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RELAY_SUPPLIED_OPTIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY_SUPPLIED_OPTIONS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOST_RESERVATION_IDENTIFIERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOST_RESERVATION_IDENTIFIERS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SANITY_CHECKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SANITY_CHECKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LEASE_CHECKS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LEASE_CHECKS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CLIENT_CLASSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REQUIRE_CLIENT_CLASSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REQUIRE_CLIENT_CLASSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TEST (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TEST, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ONLY_IF_REQUIRED (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ONLY_IF_REQUIRED, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CLIENT_CLASS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CLIENT_CLASS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RESERVATIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RESERVATIONS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_IP_ADDRESSES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESSES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PREFIXES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFIXES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DUID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DUID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HW_ADDRESS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HW_ADDRESS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTNAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTNAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLEX_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLEX_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RELAY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RELAY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_IP_ADDRESS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IP_ADDRESS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOOKS_LIBRARIES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOOKS_LIBRARIES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LIBRARY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_PARAMETERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PARAMETERS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EXPIRED_LEASES_PROCESSING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EXPIRED_LEASES_PROCESSING, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_RECLAIM_TIMER_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_RECLAIM_TIMER_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLUSH_RECLAIMED_TIMER_WAIT_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOLD_RECLAIMED_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOLD_RECLAIMED_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECLAIM_LEASES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_LEASES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_RECLAIM_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_RECLAIM_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_UNWARNED_RECLAIM_CYCLES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_UNWARNED_RECLAIM_CYCLES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LLT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LLT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_EN (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_EN, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_IDENTIFIER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_IDENTIFIER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HTYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HTYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ENTERPRISE_ID (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENTERPRISE_ID, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP4O6_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4O6_PORT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_CONTROL_SOCKET (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_SOCKET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SOCKET_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_TYPE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SOCKET_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SOCKET_NAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP_QUEUE_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP_QUEUE_CONTROL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP_DDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP_DDNS, YY_MOVE (l));
=======
  Dhcp6Parser::make_QUALIFYING_SUFFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_ENABLE_UPDATES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENABLE_UPDATES, YY_MOVE (l));
=======
  Dhcp6Parser::make_SERVER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_IP, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_QUALIFYING_SUFFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, YY_MOVE (l));
=======
  Dhcp6Parser::make_SERVER_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_PORT, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SERVER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_IP, YY_MOVE (l));
=======
  Dhcp6Parser::make_SENDER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SENDER_IP, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SERVER_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_PORT, YY_MOVE (l));
=======
  Dhcp6Parser::make_SENDER_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SENDER_PORT, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SENDER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SENDER_IP, YY_MOVE (l));
=======
  Dhcp6Parser::make_MAX_QUEUE_SIZE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SENDER_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SENDER_PORT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAX_QUEUE_SIZE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAX_QUEUE_SIZE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  Dhcp6Parser::make_NCR_PROTOCOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NCR_PROTOCOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NCR_FORMAT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NCR_FORMAT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OVERRIDE_NO_UPDATE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OVERRIDE_NO_UPDATE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OVERRIDE_CLIENT_UPDATE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OVERRIDE_CLIENT_UPDATE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_REPLACE_CLIENT_NAME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_REPLACE_CLIENT_NAME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_GENERATED_PREFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_GENERATED_PREFIX, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_UDP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_UDP, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TCP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TCP, YY_MOVE (l));
  }

<<<<<<< HEAD
<<<<<<< HEAD
    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1103,     ///< Last index in yytable_.
      yynnts_ = 405,  ///< Number of nonterminal symbols.
      yyfinal_ = 32, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 186  ///< Number of tokens.
    };
=======
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_JSON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_JSON, YY_MOVE (l));
  }
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_WHEN_PRESENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_WHEN_PRESENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_NEVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_NEVER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ALWAYS (YY_COPY (location_type) l)
  {
<<<<<<< HEAD
<<<<<<< HEAD
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185
    };
    const unsigned user_token_number_max_ = 440;
    const token_number_type undef_token_ = 2;
=======
    return symbol_type (token::TOKEN_ALWAYS, YY_MOVE (l));
  }
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
    return symbol_type (token::TOKEN_ALWAYS, YY_MOVE (l));
  }
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_WHEN_NOT_PRESENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_WHEN_NOT_PRESENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTNAME_CHAR_SET (YY_COPY (location_type) l)
  {
<<<<<<< HEAD
<<<<<<< HEAD
    switch (this->type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.move< ElementPtr > (std::move (that.value));
        break;

      case 185: // "boolean"
        value.move< bool > (std::move (that.value));
        break;

      case 184: // "floating point"
        value.move< double > (std::move (that.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (std::move (that.value));
        break;

      case 182: // "constant string"
        value.move< std::string > (std::move (that.value));
        break;
=======
    return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, YY_MOVE (l));
=======
    return symbol_type (token::TOKEN_HOSTNAME_CHAR_SET, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_HOSTNAME_CHAR_REPLACEMENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LOGGING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGING, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LOGGERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGERS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OUTPUT_OPTIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT_OPTIONS, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_HOSTNAME_CHAR_REPLACEMENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_HOSTNAME_CHAR_REPLACEMENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_LOGGING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGING, YY_MOVE (l));
=======
  Dhcp6Parser::make_OUTPUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_LOGGERS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_LOGGERS, YY_MOVE (l));
=======
  Dhcp6Parser::make_DEBUGLEVEL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DEBUGLEVEL, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_OUTPUT_OPTIONS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT_OPTIONS, YY_MOVE (l));
  }
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_OUTPUT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_OUTPUT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DEBUGLEVEL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DEBUGLEVEL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SEVERITY (YY_COPY (location_type) l)
  {
<<<<<<< HEAD
    switch (this->type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.copy< ElementPtr > (YY_MOVE (that.value));
        break;

      case 185: // "boolean"
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case 184: // "floating point"
        value.copy< double > (YY_MOVE (that.value));
        break;

      case 183: // "integer"
        value.copy< int64_t > (YY_MOVE (that.value));
        break;

      case 182: // "constant string"
        value.copy< std::string > (YY_MOVE (that.value));
        break;
=======
    return symbol_type (token::TOKEN_SEVERITY, YY_MOVE (l));
=======
  Dhcp6Parser::make_SEVERITY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SEVERITY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLUSH (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLUSH, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAXSIZE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXSIZE, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_MAXVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXVER, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCP4 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_FLUSH (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLUSH, YY_MOVE (l));
=======
  Dhcp6Parser::make_DHCPDDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCPDDNS, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_MAXSIZE (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXSIZE, YY_MOVE (l));
=======
  Dhcp6Parser::make_CONTROL_AGENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_AGENT, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_MAXVER (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_MAXVER, YY_MOVE (l));
=======
  Dhcp6Parser::make_TOPLEVEL_JSON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_JSON, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_DHCP4 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCP4, YY_MOVE (l));
  }
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCPDDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCPDDNS, YY_MOVE (l));
=======
  Dhcp6Parser::make_TOPLEVEL_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP6, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_CONTROL_AGENT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_CONTROL_AGENT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TOPLEVEL_JSON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_JSON, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_TOPLEVEL_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_TOPLEVEL_DHCP6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_DHCP6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_INTERFACES6 (YY_COPY (location_type) l)
  {
<<<<<<< HEAD
    super_type::move (s);
    switch (this->type_get ())
    {
      case 203: // value
      case 207: // map_value
      case 268: // db_type
      case 361: // hr_mode
      case 497: // duid_type
      case 532: // ncr_protocol_value
      case 539: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case 185: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case 184: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 183: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case 182: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;
=======
    return symbol_type (token::TOKEN_SUB_INTERFACES6, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_INTERFACES6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_INTERFACES6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_SUBNET6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_SUBNET6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_POOL6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_POOL6, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_PD_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_PD_POOL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_RESERVATION (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_RESERVATION, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_SUBNET6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_SUBNET6, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_OPTION_DEFS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEFS, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_POOL6 (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_POOL6, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_OPTION_DEF (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEF, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_PD_POOL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_PD_POOL, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_OPTION_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DATA, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_RESERVATION (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_RESERVATION, YY_MOVE (l));
  }
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_OPTION_DEFS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEFS, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_HOOKS_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_DHCP_DDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP_DDNS, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_OPTION_DEF (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEF, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_LOGGING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_LOGGING, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_OPTION_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DATA, YY_MOVE (l));
=======
  Dhcp6Parser::make_SUB_CONFIG_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_HOOKS_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, YY_MOVE (l));
=======
  Dhcp6Parser::make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_STRING, YY_MOVE (v), YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_DHCP_DDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP_DDNS, YY_MOVE (l));
=======
  Dhcp6Parser::make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTEGER, YY_MOVE (v), YY_MOVE (l));
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  }

  inline
  Dhcp6Parser::symbol_type
<<<<<<< HEAD
  Dhcp6Parser::make_SUB_LOGGING (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_LOGGING, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_CONFIG_CONTROL (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_CONFIG_CONTROL, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_STRING (YY_COPY (std::string) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_STRING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_INTEGER (YY_COPY (int64_t) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_INTEGER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l)
  {
<<<<<<< HEAD
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440
    };
    return token_type (yytoken_number_[type]);
  }

#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 4343 "dhcp6_parser.h"
=======
    return symbol_type (token::TOKEN_FLOAT, YY_MOVE (v), YY_MOVE (l));
  }

=======
  Dhcp6Parser::make_FLOAT (YY_COPY (double) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_FLOAT, YY_MOVE (v), YY_MOVE (l));
  }

>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_BOOLEAN, YY_MOVE (v), YY_MOVE (l));
  }
<<<<<<< HEAD
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter
=======
>>>>>>> [#805,!5-p] kea-dhcp6 now supports max-row-errors parameter


#line 14 "dhcp6_parser.yy" // lalr1.cc:404
} } // isc::dhcp
#line 3424 "dhcp6_parser.h" // lalr1.cc:404




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
