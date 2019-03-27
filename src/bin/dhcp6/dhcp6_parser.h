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

    stack (size_type n = 200)
      : seq_ (n)
    {}

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
        TOKEN_PREFERRED_LIFETIME = 298,
        TOKEN_VALID_LIFETIME = 299,
        TOKEN_RENEW_TIMER = 300,
        TOKEN_REBIND_TIMER = 301,
        TOKEN_DECLINE_PROBATION_PERIOD = 302,
        TOKEN_SERVER_TAG = 303,
        TOKEN_SUBNET6 = 304,
        TOKEN_OPTION_DEF = 305,
        TOKEN_OPTION_DATA = 306,
        TOKEN_NAME = 307,
        TOKEN_DATA = 308,
        TOKEN_CODE = 309,
        TOKEN_SPACE = 310,
        TOKEN_CSV_FORMAT = 311,
        TOKEN_ALWAYS_SEND = 312,
        TOKEN_RECORD_TYPES = 313,
        TOKEN_ENCAPSULATE = 314,
        TOKEN_ARRAY = 315,
        TOKEN_POOLS = 316,
        TOKEN_POOL = 317,
        TOKEN_PD_POOLS = 318,
        TOKEN_PREFIX = 319,
        TOKEN_PREFIX_LEN = 320,
        TOKEN_EXCLUDED_PREFIX = 321,
        TOKEN_EXCLUDED_PREFIX_LEN = 322,
        TOKEN_DELEGATED_LEN = 323,
        TOKEN_USER_CONTEXT = 324,
        TOKEN_COMMENT = 325,
        TOKEN_SUBNET = 326,
        TOKEN_INTERFACE = 327,
        TOKEN_INTERFACE_ID = 328,
        TOKEN_ID = 329,
        TOKEN_RAPID_COMMIT = 330,
        TOKEN_RESERVATION_MODE = 331,
        TOKEN_DISABLED = 332,
        TOKEN_OUT_OF_POOL = 333,
        TOKEN_GLOBAL = 334,
        TOKEN_ALL = 335,
        TOKEN_SHARED_NETWORKS = 336,
        TOKEN_MAC_SOURCES = 337,
        TOKEN_RELAY_SUPPLIED_OPTIONS = 338,
        TOKEN_HOST_RESERVATION_IDENTIFIERS = 339,
        TOKEN_SANITY_CHECKS = 340,
        TOKEN_LEASE_CHECKS = 341,
        TOKEN_CLIENT_CLASSES = 342,
        TOKEN_REQUIRE_CLIENT_CLASSES = 343,
        TOKEN_TEST = 344,
        TOKEN_ONLY_IF_REQUIRED = 345,
        TOKEN_CLIENT_CLASS = 346,
        TOKEN_RESERVATIONS = 347,
        TOKEN_IP_ADDRESSES = 348,
        TOKEN_PREFIXES = 349,
        TOKEN_DUID = 350,
        TOKEN_HW_ADDRESS = 351,
        TOKEN_HOSTNAME = 352,
        TOKEN_FLEX_ID = 353,
        TOKEN_RELAY = 354,
        TOKEN_IP_ADDRESS = 355,
        TOKEN_HOOKS_LIBRARIES = 356,
        TOKEN_LIBRARY = 357,
        TOKEN_PARAMETERS = 358,
        TOKEN_EXPIRED_LEASES_PROCESSING = 359,
        TOKEN_RECLAIM_TIMER_WAIT_TIME = 360,
        TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 361,
        TOKEN_HOLD_RECLAIMED_TIME = 362,
        TOKEN_MAX_RECLAIM_LEASES = 363,
        TOKEN_MAX_RECLAIM_TIME = 364,
        TOKEN_UNWARNED_RECLAIM_CYCLES = 365,
        TOKEN_SERVER_ID = 366,
        TOKEN_LLT = 367,
        TOKEN_EN = 368,
        TOKEN_LL = 369,
        TOKEN_IDENTIFIER = 370,
        TOKEN_HTYPE = 371,
        TOKEN_TIME = 372,
        TOKEN_ENTERPRISE_ID = 373,
        TOKEN_DHCP4O6_PORT = 374,
        TOKEN_CONTROL_SOCKET = 375,
        TOKEN_SOCKET_TYPE = 376,
        TOKEN_SOCKET_NAME = 377,
        TOKEN_DHCP_QUEUE_CONTROL = 378,
        TOKEN_DHCP_DDNS = 379,
        TOKEN_ENABLE_UPDATES = 380,
        TOKEN_QUALIFYING_SUFFIX = 381,
        TOKEN_SERVER_IP = 382,
        TOKEN_SERVER_PORT = 383,
        TOKEN_SENDER_IP = 384,
        TOKEN_SENDER_PORT = 385,
        TOKEN_MAX_QUEUE_SIZE = 386,
        TOKEN_NCR_PROTOCOL = 387,
        TOKEN_NCR_FORMAT = 388,
        TOKEN_OVERRIDE_NO_UPDATE = 389,
        TOKEN_OVERRIDE_CLIENT_UPDATE = 390,
        TOKEN_REPLACE_CLIENT_NAME = 391,
        TOKEN_GENERATED_PREFIX = 392,
        TOKEN_UDP = 393,
        TOKEN_TCP = 394,
        TOKEN_JSON = 395,
        TOKEN_WHEN_PRESENT = 396,
        TOKEN_NEVER = 397,
        TOKEN_ALWAYS = 398,
        TOKEN_WHEN_NOT_PRESENT = 399,
        TOKEN_HOSTNAME_CHAR_SET = 400,
        TOKEN_HOSTNAME_CHAR_REPLACEMENT = 401,
        TOKEN_LOGGING = 402,
        TOKEN_LOGGERS = 403,
        TOKEN_OUTPUT_OPTIONS = 404,
        TOKEN_OUTPUT = 405,
        TOKEN_DEBUGLEVEL = 406,
        TOKEN_SEVERITY = 407,
        TOKEN_FLUSH = 408,
        TOKEN_MAXSIZE = 409,
        TOKEN_MAXVER = 410,
        TOKEN_DHCP4 = 411,
        TOKEN_DHCPDDNS = 412,
        TOKEN_CONTROL_AGENT = 413,
        TOKEN_TOPLEVEL_JSON = 414,
        TOKEN_TOPLEVEL_DHCP6 = 415,
        TOKEN_SUB_DHCP6 = 416,
        TOKEN_SUB_INTERFACES6 = 417,
        TOKEN_SUB_SUBNET6 = 418,
        TOKEN_SUB_POOL6 = 419,
        TOKEN_SUB_PD_POOL = 420,
        TOKEN_SUB_RESERVATION = 421,
        TOKEN_SUB_OPTION_DEFS = 422,
        TOKEN_SUB_OPTION_DEF = 423,
        TOKEN_SUB_OPTION_DATA = 424,
        TOKEN_SUB_HOOKS_LIBRARY = 425,
        TOKEN_SUB_DHCP_DDNS = 426,
        TOKEN_SUB_LOGGING = 427,
        TOKEN_SUB_CONFIG_CONTROL = 428,
        TOKEN_STRING = 429,
        TOKEN_INTEGER = 430,
        TOKEN_FLOAT = 431,
        TOKEN_BOOLEAN = 432
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
      void clear ();

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
    typedef basic_symbol<by_type> symbol_type;

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

    // Symbol constructors declarations.
    static
    symbol_type
    make_END (YY_COPY (location_type) l);

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
    make_PREFERRED_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_VALID_LIFETIME (YY_COPY (location_type) l);

    static
    symbol_type
    make_RENEW_TIMER (YY_COPY (location_type) l);

    static
    symbol_type
    make_REBIND_TIMER (YY_COPY (location_type) l);

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
      yylast_ = 1039,     ///< Last index in yytable_.
      yynnts_ = 396,  ///< Number of nonterminal symbols.
      yyfinal_ = 32, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 178  ///< Number of tokens.
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
     175,   176,   177
    };
    const unsigned user_token_number_max_ = 432;
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (other.value));
        break;

      case 177: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (other.value));
        break;

      case 176: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (other.value));
        break;

      case 175: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (other.value));
        break;

      case 174: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.template destroy< ElementPtr > ();
        break;

      case 177: // "boolean"
        value.template destroy< bool > ();
        break;

      case 176: // "floating point"
        value.template destroy< double > ();
        break;

      case 175: // "integer"
        value.template destroy< int64_t > ();
        break;

      case 174: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 253: // db_type
      case 346: // hr_mode
      case 482: // duid_type
      case 517: // ncr_protocol_value
      case 524: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case 177: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case 176: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 175: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case 174: // "constant string"
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
     425,   426,   427,   428,   429,   430,   431,   432
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
  Dhcp6Parser::make_PREFERRED_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_PREFERRED_LIFETIME, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_VALID_LIFETIME (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_VALID_LIFETIME, YY_MOVE (l));
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
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_ENABLE_UPDATES (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_ENABLE_UPDATES, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_QUALIFYING_SUFFIX (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_QUALIFYING_SUFFIX, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_IP, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SERVER_PORT (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SERVER_PORT, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SENDER_IP (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SENDER_IP, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
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

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_JSON (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_JSON, YY_MOVE (l));
  }

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
    return symbol_type (token::TOKEN_ALWAYS, YY_MOVE (l));
  }

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
  }

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
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_DHCPDDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_DHCPDDNS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
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
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_OPTION_DEFS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEFS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_OPTION_DEF (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DEF, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_OPTION_DATA (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_OPTION_DATA, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_HOOKS_LIBRARY (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_HOOKS_LIBRARY, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_SUB_DHCP_DDNS (YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_SUB_DHCP_DDNS, YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
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
    return symbol_type (token::TOKEN_FLOAT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Dhcp6Parser::symbol_type
  Dhcp6Parser::make_BOOLEAN (YY_COPY (bool) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TOKEN_BOOLEAN, YY_MOVE (v), YY_MOVE (l));
  }


#line 14 "dhcp6_parser.yy" // lalr1.cc:404
} } // isc::dhcp
#line 3326 "dhcp6_parser.h" // lalr1.cc:404




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
