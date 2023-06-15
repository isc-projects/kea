// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_PARSER6_DHCP6_PARSER_H_INCLUDED
# define YY_PARSER6_DHCP6_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "dhcp6_parser.yy"

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp6/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 61 "dhcp6_parser.h"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
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

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef PARSER6__ASSERT
# include <cassert>
# define PARSER6__ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 210 "dhcp6_parser.h"




  /// A Bison parser.
  class Dhcp6Parser
  {
  public:
#ifdef PARSER6_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define PARSER6_STYPE in C++, use %define api.value.type"
# endif
    typedef PARSER6_STYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      PARSER6__ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      PARSER6__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      PARSER6__ASSERT (!yytypeid_);
      PARSER6__ASSERT (sizeof (T) <= size);
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
    as () YY_NOEXCEPT
    {
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == typeid (T));
      PARSER6__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == typeid (T));
      PARSER6__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      PARSER6__ASSERT (yytypeid_);
      PARSER6__ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
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
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // value
      // map_value
      // ddns_replace_client_name_value
      // db_type
      // on_fail_mode
      // hr_mode
      // duid_type
      // ncr_protocol_value
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

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOKEN_PARSER6_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_PARSER6_error = 256,     // error
    TOKEN_PARSER6_UNDEF = 257,     // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_DHCP6 = 265,             // "Dhcp6"
    TOKEN_DATA_DIRECTORY = 266,    // "data-directory"
    TOKEN_CONFIG_CONTROL = 267,    // "config-control"
    TOKEN_CONFIG_DATABASES = 268,  // "config-databases"
    TOKEN_CONFIG_FETCH_WAIT_TIME = 269, // "config-fetch-wait-time"
    TOKEN_INTERFACES_CONFIG = 270, // "interfaces-config"
    TOKEN_INTERFACES = 271,        // "interfaces"
    TOKEN_RE_DETECT = 272,         // "re-detect"
    TOKEN_SERVICE_SOCKETS_REQUIRE_ALL = 273, // "service-sockets-require-all"
    TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME = 274, // "service-sockets-retry-wait-time"
    TOKEN_SERVICE_SOCKETS_MAX_RETRIES = 275, // "service-sockets-max-retries"
    TOKEN_LEASE_DATABASE = 276,    // "lease-database"
    TOKEN_HOSTS_DATABASE = 277,    // "hosts-database"
    TOKEN_HOSTS_DATABASES = 278,   // "hosts-databases"
    TOKEN_TYPE = 279,              // "type"
    TOKEN_MEMFILE = 280,           // "memfile"
    TOKEN_MYSQL = 281,             // "mysql"
    TOKEN_POSTGRESQL = 282,        // "postgresql"
    TOKEN_USER = 283,              // "user"
    TOKEN_PASSWORD = 284,          // "password"
    TOKEN_HOST = 285,              // "host"
    TOKEN_PORT = 286,              // "port"
    TOKEN_PERSIST = 287,           // "persist"
    TOKEN_LFC_INTERVAL = 288,      // "lfc-interval"
    TOKEN_READONLY = 289,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 290,   // "connect-timeout"
    TOKEN_READ_TIMEOUT = 291,      // "read-timeout"
    TOKEN_WRITE_TIMEOUT = 292,     // "write-timeout"
    TOKEN_TCP_USER_TIMEOUT = 293,  // "tcp-user-timeout"
    TOKEN_MAX_RECONNECT_TRIES = 294, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 295, // "reconnect-wait-time"
    TOKEN_ON_FAIL = 296,           // "on-fail"
    TOKEN_STOP_RETRY_EXIT = 297,   // "stop-retry-exit"
    TOKEN_SERVE_RETRY_EXIT = 298,  // "serve-retry-exit"
    TOKEN_SERVE_RETRY_CONTINUE = 299, // "serve-retry-continue"
    TOKEN_MAX_ROW_ERRORS = 300,    // "max-row-errors"
    TOKEN_TRUST_ANCHOR = 301,      // "trust-anchor"
    TOKEN_CERT_FILE = 302,         // "cert-file"
    TOKEN_KEY_FILE = 303,          // "key-file"
    TOKEN_CIPHER_LIST = 304,       // "cipher-list"
    TOKEN_PREFERRED_LIFETIME = 305, // "preferred-lifetime"
    TOKEN_MIN_PREFERRED_LIFETIME = 306, // "min-preferred-lifetime"
    TOKEN_MAX_PREFERRED_LIFETIME = 307, // "max-preferred-lifetime"
    TOKEN_VALID_LIFETIME = 308,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 309, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 310, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 311,       // "renew-timer"
    TOKEN_REBIND_TIMER = 312,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 313, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 314,        // "t1-percent"
    TOKEN_T2_PERCENT = 315,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 316,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 317,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 318, // "decline-probation-period"
    TOKEN_SERVER_TAG = 319,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 320, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 321, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 322, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 323, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 324, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 325, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 326, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 327, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 328, // "ddns-update-on-renew"
    TOKEN_DDNS_USE_CONFLICT_RESOLUTION = 329, // "ddns-use-conflict-resolution"
    TOKEN_DDNS_TTL_PERCENT = 330,  // "ddns-ttl-percent"
    TOKEN_STORE_EXTENDED_INFO = 331, // "store-extended-info"
    TOKEN_SUBNET6 = 332,           // "subnet6"
    TOKEN_OPTION_DEF = 333,        // "option-def"
    TOKEN_OPTION_DATA = 334,       // "option-data"
    TOKEN_NAME = 335,              // "name"
    TOKEN_DATA = 336,              // "data"
    TOKEN_CODE = 337,              // "code"
    TOKEN_SPACE = 338,             // "space"
    TOKEN_CSV_FORMAT = 339,        // "csv-format"
    TOKEN_ALWAYS_SEND = 340,       // "always-send"
    TOKEN_NEVER_SEND = 341,        // "never-send"
    TOKEN_RECORD_TYPES = 342,      // "record-types"
    TOKEN_ENCAPSULATE = 343,       // "encapsulate"
    TOKEN_ARRAY = 344,             // "array"
    TOKEN_PARKED_PACKET_LIMIT = 345, // "parked-packet-limit"
    TOKEN_ALLOCATOR = 346,         // "allocator"
    TOKEN_PD_ALLOCATOR = 347,      // "pd-allocator"
    TOKEN_SHARED_NETWORKS = 348,   // "shared-networks"
    TOKEN_POOLS = 349,             // "pools"
    TOKEN_POOL = 350,              // "pool"
    TOKEN_PD_POOLS = 351,          // "pd-pools"
    TOKEN_PREFIX = 352,            // "prefix"
    TOKEN_PREFIX_LEN = 353,        // "prefix-len"
    TOKEN_EXCLUDED_PREFIX = 354,   // "excluded-prefix"
    TOKEN_EXCLUDED_PREFIX_LEN = 355, // "excluded-prefix-len"
    TOKEN_DELEGATED_LEN = 356,     // "delegated-len"
    TOKEN_USER_CONTEXT = 357,      // "user-context"
    TOKEN_COMMENT = 358,           // "comment"
    TOKEN_SUBNET = 359,            // "subnet"
    TOKEN_INTERFACE = 360,         // "interface"
    TOKEN_INTERFACE_ID = 361,      // "interface-id"
    TOKEN_ID = 362,                // "id"
    TOKEN_RAPID_COMMIT = 363,      // "rapid-commit"
    TOKEN_RESERVATION_MODE = 364,  // "reservation-mode"
    TOKEN_DISABLED = 365,          // "disabled"
    TOKEN_OUT_OF_POOL = 366,       // "out-of-pool"
    TOKEN_GLOBAL = 367,            // "global"
    TOKEN_ALL = 368,               // "all"
    TOKEN_RESERVATIONS_GLOBAL = 369, // "reservations-global"
    TOKEN_RESERVATIONS_IN_SUBNET = 370, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 371, // "reservations-out-of-pool"
    TOKEN_MAC_SOURCES = 372,       // "mac-sources"
    TOKEN_RELAY_SUPPLIED_OPTIONS = 373, // "relay-supplied-options"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 374, // "host-reservation-identifiers"
    TOKEN_SANITY_CHECKS = 375,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 376,      // "lease-checks"
    TOKEN_EXTENDED_INFO_CHECKS = 377, // "extended-info-checks"
    TOKEN_CLIENT_CLASSES = 378,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 379, // "require-client-classes"
    TOKEN_TEST = 380,              // "test"
    TOKEN_TEMPLATE_TEST = 381,     // "template-test"
    TOKEN_ONLY_IF_REQUIRED = 382,  // "only-if-required"
    TOKEN_CLIENT_CLASS = 383,      // "client-class"
    TOKEN_POOL_ID = 384,           // "pool-id"
    TOKEN_RESERVATIONS = 385,      // "reservations"
    TOKEN_IP_ADDRESSES = 386,      // "ip-addresses"
    TOKEN_PREFIXES = 387,          // "prefixes"
    TOKEN_DUID = 388,              // "duid"
    TOKEN_HW_ADDRESS = 389,        // "hw-address"
    TOKEN_HOSTNAME = 390,          // "hostname"
    TOKEN_FLEX_ID = 391,           // "flex-id"
    TOKEN_RELAY = 392,             // "relay"
    TOKEN_IP_ADDRESS = 393,        // "ip-address"
    TOKEN_HOOKS_LIBRARIES = 394,   // "hooks-libraries"
    TOKEN_LIBRARY = 395,           // "library"
    TOKEN_PARAMETERS = 396,        // "parameters"
    TOKEN_EXPIRED_LEASES_PROCESSING = 397, // "expired-leases-processing"
    TOKEN_RECLAIM_TIMER_WAIT_TIME = 398, // "reclaim-timer-wait-time"
    TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 399, // "flush-reclaimed-timer-wait-time"
    TOKEN_HOLD_RECLAIMED_TIME = 400, // "hold-reclaimed-time"
    TOKEN_MAX_RECLAIM_LEASES = 401, // "max-reclaim-leases"
    TOKEN_MAX_RECLAIM_TIME = 402,  // "max-reclaim-time"
    TOKEN_UNWARNED_RECLAIM_CYCLES = 403, // "unwarned-reclaim-cycles"
    TOKEN_SERVER_ID = 404,         // "server-id"
    TOKEN_LLT = 405,               // "LLT"
    TOKEN_EN = 406,                // "EN"
    TOKEN_LL = 407,                // "LL"
    TOKEN_IDENTIFIER = 408,        // "identifier"
    TOKEN_HTYPE = 409,             // "htype"
    TOKEN_TIME = 410,              // "time"
    TOKEN_ENTERPRISE_ID = 411,     // "enterprise-id"
    TOKEN_DHCP4O6_PORT = 412,      // "dhcp4o6-port"
    TOKEN_DHCP_MULTI_THREADING = 413, // "multi-threading"
    TOKEN_ENABLE_MULTI_THREADING = 414, // "enable-multi-threading"
    TOKEN_THREAD_POOL_SIZE = 415,  // "thread-pool-size"
    TOKEN_PACKET_QUEUE_SIZE = 416, // "packet-queue-size"
    TOKEN_CONTROL_SOCKET = 417,    // "control-socket"
    TOKEN_SOCKET_TYPE = 418,       // "socket-type"
    TOKEN_SOCKET_NAME = 419,       // "socket-name"
    TOKEN_DHCP_QUEUE_CONTROL = 420, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 421,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 422,        // "queue-type"
    TOKEN_CAPACITY = 423,          // "capacity"
    TOKEN_DHCP_DDNS = 424,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 425,    // "enable-updates"
    TOKEN_QUALIFYING_SUFFIX = 426, // "qualifying-suffix"
    TOKEN_SERVER_IP = 427,         // "server-ip"
    TOKEN_SERVER_PORT = 428,       // "server-port"
    TOKEN_SENDER_IP = 429,         // "sender-ip"
    TOKEN_SENDER_PORT = 430,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 431,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 432,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 433,        // "ncr-format"
    TOKEN_OVERRIDE_NO_UPDATE = 434, // "override-no-update"
    TOKEN_OVERRIDE_CLIENT_UPDATE = 435, // "override-client-update"
    TOKEN_REPLACE_CLIENT_NAME = 436, // "replace-client-name"
    TOKEN_GENERATED_PREFIX = 437,  // "generated-prefix"
    TOKEN_UDP = 438,               // "UDP"
    TOKEN_TCP = 439,               // "TCP"
    TOKEN_JSON = 440,              // "JSON"
    TOKEN_WHEN_PRESENT = 441,      // "when-present"
    TOKEN_NEVER = 442,             // "never"
    TOKEN_ALWAYS = 443,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 444,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 445, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 446, // "hostname-char-replacement"
    TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 447, // "early-global-reservations-lookup"
    TOKEN_IP_RESERVATIONS_UNIQUE = 448, // "ip-reservations-unique"
    TOKEN_RESERVATIONS_LOOKUP_FIRST = 449, // "reservations-lookup-first"
    TOKEN_LOGGERS = 450,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 451,    // "output_options"
    TOKEN_OUTPUT = 452,            // "output"
    TOKEN_DEBUGLEVEL = 453,        // "debuglevel"
    TOKEN_SEVERITY = 454,          // "severity"
    TOKEN_FLUSH = 455,             // "flush"
    TOKEN_MAXSIZE = 456,           // "maxsize"
    TOKEN_MAXVER = 457,            // "maxver"
    TOKEN_PATTERN = 458,           // "pattern"
    TOKEN_COMPATIBILITY = 459,     // "compatibility"
    TOKEN_LENIENT_OPTION_PARSING = 460, // "lenient-option-parsing"
    TOKEN_TOPLEVEL_JSON = 461,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP6 = 462,    // TOPLEVEL_DHCP6
    TOKEN_SUB_DHCP6 = 463,         // SUB_DHCP6
    TOKEN_SUB_INTERFACES6 = 464,   // SUB_INTERFACES6
    TOKEN_SUB_SUBNET6 = 465,       // SUB_SUBNET6
    TOKEN_SUB_POOL6 = 466,         // SUB_POOL6
    TOKEN_SUB_PD_POOL = 467,       // SUB_PD_POOL
    TOKEN_SUB_RESERVATION = 468,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 469,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 470,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 471,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 472, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 473,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 474, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 475,            // "constant string"
    TOKEN_INTEGER = 476,           // "integer"
    TOKEN_FLOAT = 477,             // "floating point"
    TOKEN_BOOLEAN = 478            // "boolean"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 224, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_COMMA = 3,                             // ","
        S_COLON = 4,                             // ":"
        S_LSQUARE_BRACKET = 5,                   // "["
        S_RSQUARE_BRACKET = 6,                   // "]"
        S_LCURLY_BRACKET = 7,                    // "{"
        S_RCURLY_BRACKET = 8,                    // "}"
        S_NULL_TYPE = 9,                         // "null"
        S_DHCP6 = 10,                            // "Dhcp6"
        S_DATA_DIRECTORY = 11,                   // "data-directory"
        S_CONFIG_CONTROL = 12,                   // "config-control"
        S_CONFIG_DATABASES = 13,                 // "config-databases"
        S_CONFIG_FETCH_WAIT_TIME = 14,           // "config-fetch-wait-time"
        S_INTERFACES_CONFIG = 15,                // "interfaces-config"
        S_INTERFACES = 16,                       // "interfaces"
        S_RE_DETECT = 17,                        // "re-detect"
        S_SERVICE_SOCKETS_REQUIRE_ALL = 18,      // "service-sockets-require-all"
        S_SERVICE_SOCKETS_RETRY_WAIT_TIME = 19,  // "service-sockets-retry-wait-time"
        S_SERVICE_SOCKETS_MAX_RETRIES = 20,      // "service-sockets-max-retries"
        S_LEASE_DATABASE = 21,                   // "lease-database"
        S_HOSTS_DATABASE = 22,                   // "hosts-database"
        S_HOSTS_DATABASES = 23,                  // "hosts-databases"
        S_TYPE = 24,                             // "type"
        S_MEMFILE = 25,                          // "memfile"
        S_MYSQL = 26,                            // "mysql"
        S_POSTGRESQL = 27,                       // "postgresql"
        S_USER = 28,                             // "user"
        S_PASSWORD = 29,                         // "password"
        S_HOST = 30,                             // "host"
        S_PORT = 31,                             // "port"
        S_PERSIST = 32,                          // "persist"
        S_LFC_INTERVAL = 33,                     // "lfc-interval"
        S_READONLY = 34,                         // "readonly"
        S_CONNECT_TIMEOUT = 35,                  // "connect-timeout"
        S_READ_TIMEOUT = 36,                     // "read-timeout"
        S_WRITE_TIMEOUT = 37,                    // "write-timeout"
        S_TCP_USER_TIMEOUT = 38,                 // "tcp-user-timeout"
        S_MAX_RECONNECT_TRIES = 39,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 40,              // "reconnect-wait-time"
        S_ON_FAIL = 41,                          // "on-fail"
        S_STOP_RETRY_EXIT = 42,                  // "stop-retry-exit"
        S_SERVE_RETRY_EXIT = 43,                 // "serve-retry-exit"
        S_SERVE_RETRY_CONTINUE = 44,             // "serve-retry-continue"
        S_MAX_ROW_ERRORS = 45,                   // "max-row-errors"
        S_TRUST_ANCHOR = 46,                     // "trust-anchor"
        S_CERT_FILE = 47,                        // "cert-file"
        S_KEY_FILE = 48,                         // "key-file"
        S_CIPHER_LIST = 49,                      // "cipher-list"
        S_PREFERRED_LIFETIME = 50,               // "preferred-lifetime"
        S_MIN_PREFERRED_LIFETIME = 51,           // "min-preferred-lifetime"
        S_MAX_PREFERRED_LIFETIME = 52,           // "max-preferred-lifetime"
        S_VALID_LIFETIME = 53,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 54,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 55,               // "max-valid-lifetime"
        S_RENEW_TIMER = 56,                      // "renew-timer"
        S_REBIND_TIMER = 57,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 58,              // "calculate-tee-times"
        S_T1_PERCENT = 59,                       // "t1-percent"
        S_T2_PERCENT = 60,                       // "t2-percent"
        S_CACHE_THRESHOLD = 61,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 62,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 63,         // "decline-probation-period"
        S_SERVER_TAG = 64,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 65,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 66,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 67,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 68,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 69,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 70,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 71,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 72,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 73,             // "ddns-update-on-renew"
        S_DDNS_USE_CONFLICT_RESOLUTION = 74,     // "ddns-use-conflict-resolution"
        S_DDNS_TTL_PERCENT = 75,                 // "ddns-ttl-percent"
        S_STORE_EXTENDED_INFO = 76,              // "store-extended-info"
        S_SUBNET6 = 77,                          // "subnet6"
        S_OPTION_DEF = 78,                       // "option-def"
        S_OPTION_DATA = 79,                      // "option-data"
        S_NAME = 80,                             // "name"
        S_DATA = 81,                             // "data"
        S_CODE = 82,                             // "code"
        S_SPACE = 83,                            // "space"
        S_CSV_FORMAT = 84,                       // "csv-format"
        S_ALWAYS_SEND = 85,                      // "always-send"
        S_NEVER_SEND = 86,                       // "never-send"
        S_RECORD_TYPES = 87,                     // "record-types"
        S_ENCAPSULATE = 88,                      // "encapsulate"
        S_ARRAY = 89,                            // "array"
        S_PARKED_PACKET_LIMIT = 90,              // "parked-packet-limit"
        S_ALLOCATOR = 91,                        // "allocator"
        S_PD_ALLOCATOR = 92,                     // "pd-allocator"
        S_SHARED_NETWORKS = 93,                  // "shared-networks"
        S_POOLS = 94,                            // "pools"
        S_POOL = 95,                             // "pool"
        S_PD_POOLS = 96,                         // "pd-pools"
        S_PREFIX = 97,                           // "prefix"
        S_PREFIX_LEN = 98,                       // "prefix-len"
        S_EXCLUDED_PREFIX = 99,                  // "excluded-prefix"
        S_EXCLUDED_PREFIX_LEN = 100,             // "excluded-prefix-len"
        S_DELEGATED_LEN = 101,                   // "delegated-len"
        S_USER_CONTEXT = 102,                    // "user-context"
        S_COMMENT = 103,                         // "comment"
        S_SUBNET = 104,                          // "subnet"
        S_INTERFACE = 105,                       // "interface"
        S_INTERFACE_ID = 106,                    // "interface-id"
        S_ID = 107,                              // "id"
        S_RAPID_COMMIT = 108,                    // "rapid-commit"
        S_RESERVATION_MODE = 109,                // "reservation-mode"
        S_DISABLED = 110,                        // "disabled"
        S_OUT_OF_POOL = 111,                     // "out-of-pool"
        S_GLOBAL = 112,                          // "global"
        S_ALL = 113,                             // "all"
        S_RESERVATIONS_GLOBAL = 114,             // "reservations-global"
        S_RESERVATIONS_IN_SUBNET = 115,          // "reservations-in-subnet"
        S_RESERVATIONS_OUT_OF_POOL = 116,        // "reservations-out-of-pool"
        S_MAC_SOURCES = 117,                     // "mac-sources"
        S_RELAY_SUPPLIED_OPTIONS = 118,          // "relay-supplied-options"
        S_HOST_RESERVATION_IDENTIFIERS = 119,    // "host-reservation-identifiers"
        S_SANITY_CHECKS = 120,                   // "sanity-checks"
        S_LEASE_CHECKS = 121,                    // "lease-checks"
        S_EXTENDED_INFO_CHECKS = 122,            // "extended-info-checks"
        S_CLIENT_CLASSES = 123,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 124,          // "require-client-classes"
        S_TEST = 125,                            // "test"
        S_TEMPLATE_TEST = 126,                   // "template-test"
        S_ONLY_IF_REQUIRED = 127,                // "only-if-required"
        S_CLIENT_CLASS = 128,                    // "client-class"
        S_POOL_ID = 129,                         // "pool-id"
        S_RESERVATIONS = 130,                    // "reservations"
        S_IP_ADDRESSES = 131,                    // "ip-addresses"
        S_PREFIXES = 132,                        // "prefixes"
        S_DUID = 133,                            // "duid"
        S_HW_ADDRESS = 134,                      // "hw-address"
        S_HOSTNAME = 135,                        // "hostname"
        S_FLEX_ID = 136,                         // "flex-id"
        S_RELAY = 137,                           // "relay"
        S_IP_ADDRESS = 138,                      // "ip-address"
        S_HOOKS_LIBRARIES = 139,                 // "hooks-libraries"
        S_LIBRARY = 140,                         // "library"
        S_PARAMETERS = 141,                      // "parameters"
        S_EXPIRED_LEASES_PROCESSING = 142,       // "expired-leases-processing"
        S_RECLAIM_TIMER_WAIT_TIME = 143,         // "reclaim-timer-wait-time"
        S_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 144, // "flush-reclaimed-timer-wait-time"
        S_HOLD_RECLAIMED_TIME = 145,             // "hold-reclaimed-time"
        S_MAX_RECLAIM_LEASES = 146,              // "max-reclaim-leases"
        S_MAX_RECLAIM_TIME = 147,                // "max-reclaim-time"
        S_UNWARNED_RECLAIM_CYCLES = 148,         // "unwarned-reclaim-cycles"
        S_SERVER_ID = 149,                       // "server-id"
        S_LLT = 150,                             // "LLT"
        S_EN = 151,                              // "EN"
        S_LL = 152,                              // "LL"
        S_IDENTIFIER = 153,                      // "identifier"
        S_HTYPE = 154,                           // "htype"
        S_TIME = 155,                            // "time"
        S_ENTERPRISE_ID = 156,                   // "enterprise-id"
        S_DHCP4O6_PORT = 157,                    // "dhcp4o6-port"
        S_DHCP_MULTI_THREADING = 158,            // "multi-threading"
        S_ENABLE_MULTI_THREADING = 159,          // "enable-multi-threading"
        S_THREAD_POOL_SIZE = 160,                // "thread-pool-size"
        S_PACKET_QUEUE_SIZE = 161,               // "packet-queue-size"
        S_CONTROL_SOCKET = 162,                  // "control-socket"
        S_SOCKET_TYPE = 163,                     // "socket-type"
        S_SOCKET_NAME = 164,                     // "socket-name"
        S_DHCP_QUEUE_CONTROL = 165,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 166,                    // "enable-queue"
        S_QUEUE_TYPE = 167,                      // "queue-type"
        S_CAPACITY = 168,                        // "capacity"
        S_DHCP_DDNS = 169,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 170,                  // "enable-updates"
        S_QUALIFYING_SUFFIX = 171,               // "qualifying-suffix"
        S_SERVER_IP = 172,                       // "server-ip"
        S_SERVER_PORT = 173,                     // "server-port"
        S_SENDER_IP = 174,                       // "sender-ip"
        S_SENDER_PORT = 175,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 176,                  // "max-queue-size"
        S_NCR_PROTOCOL = 177,                    // "ncr-protocol"
        S_NCR_FORMAT = 178,                      // "ncr-format"
        S_OVERRIDE_NO_UPDATE = 179,              // "override-no-update"
        S_OVERRIDE_CLIENT_UPDATE = 180,          // "override-client-update"
        S_REPLACE_CLIENT_NAME = 181,             // "replace-client-name"
        S_GENERATED_PREFIX = 182,                // "generated-prefix"
        S_UDP = 183,                             // "UDP"
        S_TCP = 184,                             // "TCP"
        S_JSON = 185,                            // "JSON"
        S_WHEN_PRESENT = 186,                    // "when-present"
        S_NEVER = 187,                           // "never"
        S_ALWAYS = 188,                          // "always"
        S_WHEN_NOT_PRESENT = 189,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 190,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 191,       // "hostname-char-replacement"
        S_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 192, // "early-global-reservations-lookup"
        S_IP_RESERVATIONS_UNIQUE = 193,          // "ip-reservations-unique"
        S_RESERVATIONS_LOOKUP_FIRST = 194,       // "reservations-lookup-first"
        S_LOGGERS = 195,                         // "loggers"
        S_OUTPUT_OPTIONS = 196,                  // "output_options"
        S_OUTPUT = 197,                          // "output"
        S_DEBUGLEVEL = 198,                      // "debuglevel"
        S_SEVERITY = 199,                        // "severity"
        S_FLUSH = 200,                           // "flush"
        S_MAXSIZE = 201,                         // "maxsize"
        S_MAXVER = 202,                          // "maxver"
        S_PATTERN = 203,                         // "pattern"
        S_COMPATIBILITY = 204,                   // "compatibility"
        S_LENIENT_OPTION_PARSING = 205,          // "lenient-option-parsing"
        S_TOPLEVEL_JSON = 206,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP6 = 207,                  // TOPLEVEL_DHCP6
        S_SUB_DHCP6 = 208,                       // SUB_DHCP6
        S_SUB_INTERFACES6 = 209,                 // SUB_INTERFACES6
        S_SUB_SUBNET6 = 210,                     // SUB_SUBNET6
        S_SUB_POOL6 = 211,                       // SUB_POOL6
        S_SUB_PD_POOL = 212,                     // SUB_PD_POOL
        S_SUB_RESERVATION = 213,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 214,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 215,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 216,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 217,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 218,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 219,              // SUB_CONFIG_CONTROL
        S_STRING = 220,                          // "constant string"
        S_INTEGER = 221,                         // "integer"
        S_FLOAT = 222,                           // "floating point"
        S_BOOLEAN = 223,                         // "boolean"
        S_YYACCEPT = 224,                        // $accept
        S_start = 225,                           // start
        S_226_1 = 226,                           // $@1
        S_227_2 = 227,                           // $@2
        S_228_3 = 228,                           // $@3
        S_229_4 = 229,                           // $@4
        S_230_5 = 230,                           // $@5
        S_231_6 = 231,                           // $@6
        S_232_7 = 232,                           // $@7
        S_233_8 = 233,                           // $@8
        S_234_9 = 234,                           // $@9
        S_235_10 = 235,                          // $@10
        S_236_11 = 236,                          // $@11
        S_237_12 = 237,                          // $@12
        S_238_13 = 238,                          // $@13
        S_239_14 = 239,                          // $@14
        S_value = 240,                           // value
        S_sub_json = 241,                        // sub_json
        S_map2 = 242,                            // map2
        S_243_15 = 243,                          // $@15
        S_map_value = 244,                       // map_value
        S_map_content = 245,                     // map_content
        S_not_empty_map = 246,                   // not_empty_map
        S_list_generic = 247,                    // list_generic
        S_248_16 = 248,                          // $@16
        S_list_content = 249,                    // list_content
        S_not_empty_list = 250,                  // not_empty_list
        S_list_strings = 251,                    // list_strings
        S_252_17 = 252,                          // $@17
        S_list_strings_content = 253,            // list_strings_content
        S_not_empty_list_strings = 254,          // not_empty_list_strings
        S_unknown_map_entry = 255,               // unknown_map_entry
        S_syntax_map = 256,                      // syntax_map
        S_257_18 = 257,                          // $@18
        S_global_object = 258,                   // global_object
        S_259_19 = 259,                          // $@19
        S_global_object_comma = 260,             // global_object_comma
        S_sub_dhcp6 = 261,                       // sub_dhcp6
        S_262_20 = 262,                          // $@20
        S_global_params = 263,                   // global_params
        S_global_param = 264,                    // global_param
        S_data_directory = 265,                  // data_directory
        S_266_21 = 266,                          // $@21
        S_preferred_lifetime = 267,              // preferred_lifetime
        S_min_preferred_lifetime = 268,          // min_preferred_lifetime
        S_max_preferred_lifetime = 269,          // max_preferred_lifetime
        S_valid_lifetime = 270,                  // valid_lifetime
        S_min_valid_lifetime = 271,              // min_valid_lifetime
        S_max_valid_lifetime = 272,              // max_valid_lifetime
        S_renew_timer = 273,                     // renew_timer
        S_rebind_timer = 274,                    // rebind_timer
        S_calculate_tee_times = 275,             // calculate_tee_times
        S_t1_percent = 276,                      // t1_percent
        S_t2_percent = 277,                      // t2_percent
        S_cache_threshold = 278,                 // cache_threshold
        S_cache_max_age = 279,                   // cache_max_age
        S_decline_probation_period = 280,        // decline_probation_period
        S_ddns_send_updates = 281,               // ddns_send_updates
        S_ddns_override_no_update = 282,         // ddns_override_no_update
        S_ddns_override_client_update = 283,     // ddns_override_client_update
        S_ddns_replace_client_name = 284,        // ddns_replace_client_name
        S_285_22 = 285,                          // $@22
        S_ddns_replace_client_name_value = 286,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 287,           // ddns_generated_prefix
        S_288_23 = 288,                          // $@23
        S_ddns_qualifying_suffix = 289,          // ddns_qualifying_suffix
        S_290_24 = 290,                          // $@24
        S_ddns_update_on_renew = 291,            // ddns_update_on_renew
        S_ddns_use_conflict_resolution = 292,    // ddns_use_conflict_resolution
        S_ddns_ttl_percent = 293,                // ddns_ttl_percent
        S_hostname_char_set = 294,               // hostname_char_set
        S_295_25 = 295,                          // $@25
        S_hostname_char_replacement = 296,       // hostname_char_replacement
        S_297_26 = 297,                          // $@26
        S_store_extended_info = 298,             // store_extended_info
        S_statistic_default_sample_count = 299,  // statistic_default_sample_count
        S_statistic_default_sample_age = 300,    // statistic_default_sample_age
        S_server_tag = 301,                      // server_tag
        S_302_27 = 302,                          // $@27
        S_parked_packet_limit = 303,             // parked_packet_limit
        S_allocator = 304,                       // allocator
        S_305_28 = 305,                          // $@28
        S_pd_allocator = 306,                    // pd_allocator
        S_307_29 = 307,                          // $@29
        S_early_global_reservations_lookup = 308, // early_global_reservations_lookup
        S_ip_reservations_unique = 309,          // ip_reservations_unique
        S_reservations_lookup_first = 310,       // reservations_lookup_first
        S_interfaces_config = 311,               // interfaces_config
        S_312_30 = 312,                          // $@30
        S_sub_interfaces6 = 313,                 // sub_interfaces6
        S_314_31 = 314,                          // $@31
        S_interfaces_config_params = 315,        // interfaces_config_params
        S_interfaces_config_param = 316,         // interfaces_config_param
        S_interfaces_list = 317,                 // interfaces_list
        S_318_32 = 318,                          // $@32
        S_re_detect = 319,                       // re_detect
        S_service_sockets_require_all = 320,     // service_sockets_require_all
        S_service_sockets_retry_wait_time = 321, // service_sockets_retry_wait_time
        S_service_sockets_max_retries = 322,     // service_sockets_max_retries
        S_lease_database = 323,                  // lease_database
        S_324_33 = 324,                          // $@33
        S_hosts_database = 325,                  // hosts_database
        S_326_34 = 326,                          // $@34
        S_hosts_databases = 327,                 // hosts_databases
        S_328_35 = 328,                          // $@35
        S_database_list = 329,                   // database_list
        S_not_empty_database_list = 330,         // not_empty_database_list
        S_database = 331,                        // database
        S_332_36 = 332,                          // $@36
        S_database_map_params = 333,             // database_map_params
        S_database_map_param = 334,              // database_map_param
        S_database_type = 335,                   // database_type
        S_336_37 = 336,                          // $@37
        S_db_type = 337,                         // db_type
        S_user = 338,                            // user
        S_339_38 = 339,                          // $@38
        S_password = 340,                        // password
        S_341_39 = 341,                          // $@39
        S_host = 342,                            // host
        S_343_40 = 343,                          // $@40
        S_port = 344,                            // port
        S_name = 345,                            // name
        S_346_41 = 346,                          // $@41
        S_persist = 347,                         // persist
        S_lfc_interval = 348,                    // lfc_interval
        S_readonly = 349,                        // readonly
        S_connect_timeout = 350,                 // connect_timeout
        S_read_timeout = 351,                    // read_timeout
        S_write_timeout = 352,                   // write_timeout
        S_tcp_user_timeout = 353,                // tcp_user_timeout
        S_reconnect_wait_time = 354,             // reconnect_wait_time
        S_on_fail = 355,                         // on_fail
        S_356_42 = 356,                          // $@42
        S_on_fail_mode = 357,                    // on_fail_mode
        S_max_row_errors = 358,                  // max_row_errors
        S_max_reconnect_tries = 359,             // max_reconnect_tries
        S_trust_anchor = 360,                    // trust_anchor
        S_361_43 = 361,                          // $@43
        S_cert_file = 362,                       // cert_file
        S_363_44 = 363,                          // $@44
        S_key_file = 364,                        // key_file
        S_365_45 = 365,                          // $@45
        S_cipher_list = 366,                     // cipher_list
        S_367_46 = 367,                          // $@46
        S_sanity_checks = 368,                   // sanity_checks
        S_369_47 = 369,                          // $@47
        S_sanity_checks_params = 370,            // sanity_checks_params
        S_sanity_checks_param = 371,             // sanity_checks_param
        S_lease_checks = 372,                    // lease_checks
        S_373_48 = 373,                          // $@48
        S_extended_info_checks = 374,            // extended_info_checks
        S_375_49 = 375,                          // $@49
        S_mac_sources = 376,                     // mac_sources
        S_377_50 = 377,                          // $@50
        S_mac_sources_list = 378,                // mac_sources_list
        S_mac_sources_value = 379,               // mac_sources_value
        S_duid_id = 380,                         // duid_id
        S_string_id = 381,                       // string_id
        S_host_reservation_identifiers = 382,    // host_reservation_identifiers
        S_383_51 = 383,                          // $@51
        S_host_reservation_identifiers_list = 384, // host_reservation_identifiers_list
        S_host_reservation_identifier = 385,     // host_reservation_identifier
        S_hw_address_id = 386,                   // hw_address_id
        S_flex_id = 387,                         // flex_id
        S_relay_supplied_options = 388,          // relay_supplied_options
        S_389_52 = 389,                          // $@52
        S_dhcp_multi_threading = 390,            // dhcp_multi_threading
        S_391_53 = 391,                          // $@53
        S_multi_threading_params = 392,          // multi_threading_params
        S_multi_threading_param = 393,           // multi_threading_param
        S_enable_multi_threading = 394,          // enable_multi_threading
        S_thread_pool_size = 395,                // thread_pool_size
        S_packet_queue_size = 396,               // packet_queue_size
        S_hooks_libraries = 397,                 // hooks_libraries
        S_398_54 = 398,                          // $@54
        S_hooks_libraries_list = 399,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 400,  // not_empty_hooks_libraries_list
        S_hooks_library = 401,                   // hooks_library
        S_402_55 = 402,                          // $@55
        S_sub_hooks_library = 403,               // sub_hooks_library
        S_404_56 = 404,                          // $@56
        S_hooks_params = 405,                    // hooks_params
        S_hooks_param = 406,                     // hooks_param
        S_library = 407,                         // library
        S_408_57 = 408,                          // $@57
        S_parameters = 409,                      // parameters
        S_410_58 = 410,                          // $@58
        S_expired_leases_processing = 411,       // expired_leases_processing
        S_412_59 = 412,                          // $@59
        S_expired_leases_params = 413,           // expired_leases_params
        S_expired_leases_param = 414,            // expired_leases_param
        S_reclaim_timer_wait_time = 415,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 416, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 417,             // hold_reclaimed_time
        S_max_reclaim_leases = 418,              // max_reclaim_leases
        S_max_reclaim_time = 419,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 420,         // unwarned_reclaim_cycles
        S_subnet6_list = 421,                    // subnet6_list
        S_422_60 = 422,                          // $@60
        S_subnet6_list_content = 423,            // subnet6_list_content
        S_not_empty_subnet6_list = 424,          // not_empty_subnet6_list
        S_subnet6 = 425,                         // subnet6
        S_426_61 = 426,                          // $@61
        S_sub_subnet6 = 427,                     // sub_subnet6
        S_428_62 = 428,                          // $@62
        S_subnet6_params = 429,                  // subnet6_params
        S_subnet6_param = 430,                   // subnet6_param
        S_subnet = 431,                          // subnet
        S_432_63 = 432,                          // $@63
        S_interface = 433,                       // interface
        S_434_64 = 434,                          // $@64
        S_interface_id = 435,                    // interface_id
        S_436_65 = 436,                          // $@65
        S_client_class = 437,                    // client_class
        S_438_66 = 438,                          // $@66
        S_require_client_classes = 439,          // require_client_classes
        S_440_67 = 440,                          // $@67
        S_reservations_global = 441,             // reservations_global
        S_reservations_in_subnet = 442,          // reservations_in_subnet
        S_reservations_out_of_pool = 443,        // reservations_out_of_pool
        S_reservation_mode = 444,                // reservation_mode
        S_445_68 = 445,                          // $@68
        S_hr_mode = 446,                         // hr_mode
        S_id = 447,                              // id
        S_rapid_commit = 448,                    // rapid_commit
        S_shared_networks = 449,                 // shared_networks
        S_450_69 = 450,                          // $@69
        S_shared_networks_content = 451,         // shared_networks_content
        S_shared_networks_list = 452,            // shared_networks_list
        S_shared_network = 453,                  // shared_network
        S_454_70 = 454,                          // $@70
        S_shared_network_params = 455,           // shared_network_params
        S_shared_network_param = 456,            // shared_network_param
        S_option_def_list = 457,                 // option_def_list
        S_458_71 = 458,                          // $@71
        S_sub_option_def_list = 459,             // sub_option_def_list
        S_460_72 = 460,                          // $@72
        S_option_def_list_content = 461,         // option_def_list_content
        S_not_empty_option_def_list = 462,       // not_empty_option_def_list
        S_option_def_entry = 463,                // option_def_entry
        S_464_73 = 464,                          // $@73
        S_sub_option_def = 465,                  // sub_option_def
        S_466_74 = 466,                          // $@74
        S_option_def_params = 467,               // option_def_params
        S_not_empty_option_def_params = 468,     // not_empty_option_def_params
        S_option_def_param = 469,                // option_def_param
        S_option_def_name = 470,                 // option_def_name
        S_code = 471,                            // code
        S_option_def_code = 472,                 // option_def_code
        S_option_def_type = 473,                 // option_def_type
        S_474_75 = 474,                          // $@75
        S_option_def_record_types = 475,         // option_def_record_types
        S_476_76 = 476,                          // $@76
        S_space = 477,                           // space
        S_478_77 = 478,                          // $@77
        S_option_def_space = 479,                // option_def_space
        S_option_def_encapsulate = 480,          // option_def_encapsulate
        S_481_78 = 481,                          // $@78
        S_option_def_array = 482,                // option_def_array
        S_option_data_list = 483,                // option_data_list
        S_484_79 = 484,                          // $@79
        S_option_data_list_content = 485,        // option_data_list_content
        S_not_empty_option_data_list = 486,      // not_empty_option_data_list
        S_option_data_entry = 487,               // option_data_entry
        S_488_80 = 488,                          // $@80
        S_sub_option_data = 489,                 // sub_option_data
        S_490_81 = 490,                          // $@81
        S_option_data_params = 491,              // option_data_params
        S_not_empty_option_data_params = 492,    // not_empty_option_data_params
        S_option_data_param = 493,               // option_data_param
        S_option_data_name = 494,                // option_data_name
        S_option_data_data = 495,                // option_data_data
        S_496_82 = 496,                          // $@82
        S_option_data_code = 497,                // option_data_code
        S_option_data_space = 498,               // option_data_space
        S_option_data_csv_format = 499,          // option_data_csv_format
        S_option_data_always_send = 500,         // option_data_always_send
        S_option_data_never_send = 501,          // option_data_never_send
        S_pools_list = 502,                      // pools_list
        S_503_83 = 503,                          // $@83
        S_pools_list_content = 504,              // pools_list_content
        S_not_empty_pools_list = 505,            // not_empty_pools_list
        S_pool_list_entry = 506,                 // pool_list_entry
        S_507_84 = 507,                          // $@84
        S_sub_pool6 = 508,                       // sub_pool6
        S_509_85 = 509,                          // $@85
        S_pool_params = 510,                     // pool_params
        S_pool_param = 511,                      // pool_param
        S_pool_entry = 512,                      // pool_entry
        S_513_86 = 513,                          // $@86
        S_user_context = 514,                    // user_context
        S_515_87 = 515,                          // $@87
        S_comment = 516,                         // comment
        S_517_88 = 517,                          // $@88
        S_pd_pools_list = 518,                   // pd_pools_list
        S_519_89 = 519,                          // $@89
        S_pd_pools_list_content = 520,           // pd_pools_list_content
        S_not_empty_pd_pools_list = 521,         // not_empty_pd_pools_list
        S_pd_pool_entry = 522,                   // pd_pool_entry
        S_523_90 = 523,                          // $@90
        S_sub_pd_pool = 524,                     // sub_pd_pool
        S_525_91 = 525,                          // $@91
        S_pd_pool_params = 526,                  // pd_pool_params
        S_pd_pool_param = 527,                   // pd_pool_param
        S_pd_prefix = 528,                       // pd_prefix
        S_529_92 = 529,                          // $@92
        S_pd_prefix_len = 530,                   // pd_prefix_len
        S_excluded_prefix = 531,                 // excluded_prefix
        S_532_93 = 532,                          // $@93
        S_excluded_prefix_len = 533,             // excluded_prefix_len
        S_pd_delegated_len = 534,                // pd_delegated_len
        S_reservations = 535,                    // reservations
        S_536_94 = 536,                          // $@94
        S_reservations_list = 537,               // reservations_list
        S_not_empty_reservations_list = 538,     // not_empty_reservations_list
        S_reservation = 539,                     // reservation
        S_540_95 = 540,                          // $@95
        S_sub_reservation = 541,                 // sub_reservation
        S_542_96 = 542,                          // $@96
        S_reservation_params = 543,              // reservation_params
        S_not_empty_reservation_params = 544,    // not_empty_reservation_params
        S_reservation_param = 545,               // reservation_param
        S_ip_addresses = 546,                    // ip_addresses
        S_547_97 = 547,                          // $@97
        S_prefixes = 548,                        // prefixes
        S_549_98 = 549,                          // $@98
        S_duid = 550,                            // duid
        S_551_99 = 551,                          // $@99
        S_hw_address = 552,                      // hw_address
        S_553_100 = 553,                         // $@100
        S_hostname = 554,                        // hostname
        S_555_101 = 555,                         // $@101
        S_flex_id_value = 556,                   // flex_id_value
        S_557_102 = 557,                         // $@102
        S_reservation_client_classes = 558,      // reservation_client_classes
        S_559_103 = 559,                         // $@103
        S_relay = 560,                           // relay
        S_561_104 = 561,                         // $@104
        S_relay_map = 562,                       // relay_map
        S_ip_address = 563,                      // ip_address
        S_564_105 = 564,                         // $@105
        S_client_classes = 565,                  // client_classes
        S_566_106 = 566,                         // $@106
        S_client_classes_list = 567,             // client_classes_list
        S_client_class_entry = 568,              // client_class_entry
        S_569_107 = 569,                         // $@107
        S_client_class_params = 570,             // client_class_params
        S_not_empty_client_class_params = 571,   // not_empty_client_class_params
        S_client_class_param = 572,              // client_class_param
        S_client_class_name = 573,               // client_class_name
        S_client_class_test = 574,               // client_class_test
        S_575_108 = 575,                         // $@108
        S_client_class_template_test = 576,      // client_class_template_test
        S_577_109 = 577,                         // $@109
        S_only_if_required = 578,                // only_if_required
        S_server_id = 579,                       // server_id
        S_580_110 = 580,                         // $@110
        S_server_id_params = 581,                // server_id_params
        S_server_id_param = 582,                 // server_id_param
        S_server_id_type = 583,                  // server_id_type
        S_584_111 = 584,                         // $@111
        S_duid_type = 585,                       // duid_type
        S_htype = 586,                           // htype
        S_identifier = 587,                      // identifier
        S_588_112 = 588,                         // $@112
        S_time = 589,                            // time
        S_enterprise_id = 590,                   // enterprise_id
        S_dhcp4o6_port = 591,                    // dhcp4o6_port
        S_control_socket = 592,                  // control_socket
        S_593_113 = 593,                         // $@113
        S_control_socket_params = 594,           // control_socket_params
        S_control_socket_param = 595,            // control_socket_param
        S_socket_type = 596,                     // socket_type
        S_597_114 = 597,                         // $@114
        S_socket_name = 598,                     // socket_name
        S_599_115 = 599,                         // $@115
        S_dhcp_queue_control = 600,              // dhcp_queue_control
        S_601_116 = 601,                         // $@116
        S_queue_control_params = 602,            // queue_control_params
        S_queue_control_param = 603,             // queue_control_param
        S_enable_queue = 604,                    // enable_queue
        S_queue_type = 605,                      // queue_type
        S_606_117 = 606,                         // $@117
        S_capacity = 607,                        // capacity
        S_arbitrary_map_entry = 608,             // arbitrary_map_entry
        S_609_118 = 609,                         // $@118
        S_dhcp_ddns = 610,                       // dhcp_ddns
        S_611_119 = 611,                         // $@119
        S_sub_dhcp_ddns = 612,                   // sub_dhcp_ddns
        S_613_120 = 613,                         // $@120
        S_dhcp_ddns_params = 614,                // dhcp_ddns_params
        S_dhcp_ddns_param = 615,                 // dhcp_ddns_param
        S_enable_updates = 616,                  // enable_updates
        S_dep_qualifying_suffix = 617,           // dep_qualifying_suffix
        S_618_121 = 618,                         // $@121
        S_server_ip = 619,                       // server_ip
        S_620_122 = 620,                         // $@122
        S_server_port = 621,                     // server_port
        S_sender_ip = 622,                       // sender_ip
        S_623_123 = 623,                         // $@123
        S_sender_port = 624,                     // sender_port
        S_max_queue_size = 625,                  // max_queue_size
        S_ncr_protocol = 626,                    // ncr_protocol
        S_627_124 = 627,                         // $@124
        S_ncr_protocol_value = 628,              // ncr_protocol_value
        S_ncr_format = 629,                      // ncr_format
        S_630_125 = 630,                         // $@125
        S_dep_override_no_update = 631,          // dep_override_no_update
        S_dep_override_client_update = 632,      // dep_override_client_update
        S_dep_replace_client_name = 633,         // dep_replace_client_name
        S_634_126 = 634,                         // $@126
        S_dep_generated_prefix = 635,            // dep_generated_prefix
        S_636_127 = 636,                         // $@127
        S_dep_hostname_char_set = 637,           // dep_hostname_char_set
        S_638_128 = 638,                         // $@128
        S_dep_hostname_char_replacement = 639,   // dep_hostname_char_replacement
        S_640_129 = 640,                         // $@129
        S_config_control = 641,                  // config_control
        S_642_130 = 642,                         // $@130
        S_sub_config_control = 643,              // sub_config_control
        S_644_131 = 644,                         // $@131
        S_config_control_params = 645,           // config_control_params
        S_config_control_param = 646,            // config_control_param
        S_config_databases = 647,                // config_databases
        S_648_132 = 648,                         // $@132
        S_config_fetch_wait_time = 649,          // config_fetch_wait_time
        S_loggers = 650,                         // loggers
        S_651_133 = 651,                         // $@133
        S_loggers_entries = 652,                 // loggers_entries
        S_logger_entry = 653,                    // logger_entry
        S_654_134 = 654,                         // $@134
        S_logger_params = 655,                   // logger_params
        S_logger_param = 656,                    // logger_param
        S_debuglevel = 657,                      // debuglevel
        S_severity = 658,                        // severity
        S_659_135 = 659,                         // $@135
        S_output_options_list = 660,             // output_options_list
        S_661_136 = 661,                         // $@136
        S_output_options_list_content = 662,     // output_options_list_content
        S_output_entry = 663,                    // output_entry
        S_664_137 = 664,                         // $@137
        S_output_params_list = 665,              // output_params_list
        S_output_params = 666,                   // output_params
        S_output = 667,                          // output
        S_668_138 = 668,                         // $@138
        S_flush = 669,                           // flush
        S_maxsize = 670,                         // maxsize
        S_maxver = 671,                          // maxver
        S_pattern = 672,                         // pattern
        S_673_139 = 673,                         // $@139
        S_compatibility = 674,                   // compatibility
        S_675_140 = 675,                         // $@140
        S_compatibility_params = 676,            // compatibility_params
        S_compatibility_param = 677,             // compatibility_param
        S_lenient_option_parsing = 678           // lenient_option_parsing
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.move< ElementPtr > (std::move (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (std::move (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ElementPtr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ElementPtr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int64_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int64_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.template destroy< ElementPtr > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.template destroy< double > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.template destroy< int64_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Dhcp6Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        PARSER6__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_PARSER6_error <= tok && tok <= token::TOKEN_SUB_CONFIG_CONTROL));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        PARSER6__ASSERT (tok == token::TOKEN_BOOLEAN);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        PARSER6__ASSERT (tok == token::TOKEN_FLOAT);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int64_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        PARSER6__ASSERT (tok == token::TOKEN_INTEGER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        PARSER6__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
    };

    /// Build a parser object.
    Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg);
    virtual ~Dhcp6Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Dhcp6Parser (const Dhcp6Parser&) = delete;
    /// Non copyable.
    Dhcp6Parser& operator= (const Dhcp6Parser&) = delete;
#endif

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

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
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
      make_PARSER6_error (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER6_error, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER6_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER6_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARSER6_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER6_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER6_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER6_UNDEF, l);
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
      make_SERVICE_SOCKETS_REQUIRE_ALL (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_REQUIRE_ALL, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_REQUIRE_ALL (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_REQUIRE_ALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVICE_SOCKETS_RETRY_WAIT_TIME (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_RETRY_WAIT_TIME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVICE_SOCKETS_MAX_RETRIES (location_type l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_MAX_RETRIES, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVICE_SOCKETS_MAX_RETRIES (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVICE_SOCKETS_MAX_RETRIES, l);
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
      make_READ_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_READ_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_READ_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_READ_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WRITE_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_WRITE_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_WRITE_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_WRITE_TIMEOUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TCP_USER_TIMEOUT (location_type l)
      {
        return symbol_type (token::TOKEN_TCP_USER_TIMEOUT, std::move (l));
      }
#else
      static
      symbol_type
      make_TCP_USER_TIMEOUT (const location_type& l)
      {
        return symbol_type (token::TOKEN_TCP_USER_TIMEOUT, l);
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
      make_ON_FAIL (location_type l)
      {
        return symbol_type (token::TOKEN_ON_FAIL, std::move (l));
      }
#else
      static
      symbol_type
      make_ON_FAIL (const location_type& l)
      {
        return symbol_type (token::TOKEN_ON_FAIL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STOP_RETRY_EXIT (location_type l)
      {
        return symbol_type (token::TOKEN_STOP_RETRY_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_STOP_RETRY_EXIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_STOP_RETRY_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVE_RETRY_EXIT (location_type l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVE_RETRY_EXIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVE_RETRY_CONTINUE (location_type l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_CONTINUE, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVE_RETRY_CONTINUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVE_RETRY_CONTINUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAX_ROW_ERRORS (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_ROW_ERRORS, std::move (l));
      }
#else
      static
      symbol_type
      make_MAX_ROW_ERRORS (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_ROW_ERRORS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUST_ANCHOR (location_type l)
      {
        return symbol_type (token::TOKEN_TRUST_ANCHOR, std::move (l));
      }
#else
      static
      symbol_type
      make_TRUST_ANCHOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_TRUST_ANCHOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CERT_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_CERT_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_CERT_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CERT_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEY_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_KEY_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KEY_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_KEY_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CIPHER_LIST (location_type l)
      {
        return symbol_type (token::TOKEN_CIPHER_LIST, std::move (l));
      }
#else
      static
      symbol_type
      make_CIPHER_LIST (const location_type& l)
      {
        return symbol_type (token::TOKEN_CIPHER_LIST, l);
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
      make_CACHE_THRESHOLD (location_type l)
      {
        return symbol_type (token::TOKEN_CACHE_THRESHOLD, std::move (l));
      }
#else
      static
      symbol_type
      make_CACHE_THRESHOLD (const location_type& l)
      {
        return symbol_type (token::TOKEN_CACHE_THRESHOLD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CACHE_MAX_AGE (location_type l)
      {
        return symbol_type (token::TOKEN_CACHE_MAX_AGE, std::move (l));
      }
#else
      static
      symbol_type
      make_CACHE_MAX_AGE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CACHE_MAX_AGE, l);
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
      make_STATISTIC_DEFAULT_SAMPLE_COUNT (location_type l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT, std::move (l));
      }
#else
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_COUNT (const location_type& l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_AGE (location_type l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE, std::move (l));
      }
#else
      static
      symbol_type
      make_STATISTIC_DEFAULT_SAMPLE_AGE (const location_type& l)
      {
        return symbol_type (token::TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_SEND_UPDATES (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_SEND_UPDATES, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_SEND_UPDATES (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_SEND_UPDATES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_OVERRIDE_NO_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_NO_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_OVERRIDE_NO_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_NO_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_OVERRIDE_CLIENT_UPDATE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_OVERRIDE_CLIENT_UPDATE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_REPLACE_CLIENT_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_REPLACE_CLIENT_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_REPLACE_CLIENT_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_REPLACE_CLIENT_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_GENERATED_PREFIX (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_GENERATED_PREFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_GENERATED_PREFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_GENERATED_PREFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_QUALIFYING_SUFFIX (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_QUALIFYING_SUFFIX, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_QUALIFYING_SUFFIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_QUALIFYING_SUFFIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_UPDATE_ON_RENEW (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_UPDATE_ON_RENEW, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_UPDATE_ON_RENEW (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_UPDATE_ON_RENEW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_USE_CONFLICT_RESOLUTION (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_USE_CONFLICT_RESOLUTION, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_USE_CONFLICT_RESOLUTION (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_USE_CONFLICT_RESOLUTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_TTL_PERCENT (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_PERCENT, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_TTL_PERCENT (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_PERCENT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STORE_EXTENDED_INFO (location_type l)
      {
        return symbol_type (token::TOKEN_STORE_EXTENDED_INFO, std::move (l));
      }
#else
      static
      symbol_type
      make_STORE_EXTENDED_INFO (const location_type& l)
      {
        return symbol_type (token::TOKEN_STORE_EXTENDED_INFO, l);
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
      make_NEVER_SEND (location_type l)
      {
        return symbol_type (token::TOKEN_NEVER_SEND, std::move (l));
      }
#else
      static
      symbol_type
      make_NEVER_SEND (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEVER_SEND, l);
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
      make_PARKED_PACKET_LIMIT (location_type l)
      {
        return symbol_type (token::TOKEN_PARKED_PACKET_LIMIT, std::move (l));
      }
#else
      static
      symbol_type
      make_PARKED_PACKET_LIMIT (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARKED_PACKET_LIMIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ALLOCATOR (location_type l)
      {
        return symbol_type (token::TOKEN_ALLOCATOR, std::move (l));
      }
#else
      static
      symbol_type
      make_ALLOCATOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_ALLOCATOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PD_ALLOCATOR (location_type l)
      {
        return symbol_type (token::TOKEN_PD_ALLOCATOR, std::move (l));
      }
#else
      static
      symbol_type
      make_PD_ALLOCATOR (const location_type& l)
      {
        return symbol_type (token::TOKEN_PD_ALLOCATOR, l);
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
      make_RESERVATIONS_GLOBAL (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_GLOBAL, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_GLOBAL (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_GLOBAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_IN_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_IN_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_IN_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_IN_SUBNET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_OUT_OF_POOL (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_OUT_OF_POOL, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_OUT_OF_POOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_OUT_OF_POOL, l);
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
      make_EXTENDED_INFO_CHECKS (location_type l)
      {
        return symbol_type (token::TOKEN_EXTENDED_INFO_CHECKS, std::move (l));
      }
#else
      static
      symbol_type
      make_EXTENDED_INFO_CHECKS (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXTENDED_INFO_CHECKS, l);
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
      make_TEMPLATE_TEST (location_type l)
      {
        return symbol_type (token::TOKEN_TEMPLATE_TEST, std::move (l));
      }
#else
      static
      symbol_type
      make_TEMPLATE_TEST (const location_type& l)
      {
        return symbol_type (token::TOKEN_TEMPLATE_TEST, l);
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
      make_POOL_ID (location_type l)
      {
        return symbol_type (token::TOKEN_POOL_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_POOL_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_POOL_ID, l);
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
      make_DHCP_MULTI_THREADING (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_MULTI_THREADING, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_MULTI_THREADING (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_MULTI_THREADING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENABLE_MULTI_THREADING (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_MULTI_THREADING, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_MULTI_THREADING (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_MULTI_THREADING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THREAD_POOL_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_THREAD_POOL_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_THREAD_POOL_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_THREAD_POOL_SIZE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PACKET_QUEUE_SIZE (location_type l)
      {
        return symbol_type (token::TOKEN_PACKET_QUEUE_SIZE, std::move (l));
      }
#else
      static
      symbol_type
      make_PACKET_QUEUE_SIZE (const location_type& l)
      {
        return symbol_type (token::TOKEN_PACKET_QUEUE_SIZE, l);
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
      make_ENABLE_QUEUE (location_type l)
      {
        return symbol_type (token::TOKEN_ENABLE_QUEUE, std::move (l));
      }
#else
      static
      symbol_type
      make_ENABLE_QUEUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ENABLE_QUEUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QUEUE_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_QUEUE_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_QUEUE_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_QUEUE_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CAPACITY (location_type l)
      {
        return symbol_type (token::TOKEN_CAPACITY, std::move (l));
      }
#else
      static
      symbol_type
      make_CAPACITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_CAPACITY, l);
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
      make_EARLY_GLOBAL_RESERVATIONS_LOOKUP (location_type l)
      {
        return symbol_type (token::TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP, std::move (l));
      }
#else
      static
      symbol_type
      make_EARLY_GLOBAL_RESERVATIONS_LOOKUP (const location_type& l)
      {
        return symbol_type (token::TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IP_RESERVATIONS_UNIQUE (location_type l)
      {
        return symbol_type (token::TOKEN_IP_RESERVATIONS_UNIQUE, std::move (l));
      }
#else
      static
      symbol_type
      make_IP_RESERVATIONS_UNIQUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_IP_RESERVATIONS_UNIQUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RESERVATIONS_LOOKUP_FIRST (location_type l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_LOOKUP_FIRST, std::move (l));
      }
#else
      static
      symbol_type
      make_RESERVATIONS_LOOKUP_FIRST (const location_type& l)
      {
        return symbol_type (token::TOKEN_RESERVATIONS_LOOKUP_FIRST, l);
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
      make_COMPATIBILITY (location_type l)
      {
        return symbol_type (token::TOKEN_COMPATIBILITY, std::move (l));
      }
#else
      static
      symbol_type
      make_COMPATIBILITY (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMPATIBILITY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LENIENT_OPTION_PARSING (location_type l)
      {
        return symbol_type (token::TOKEN_LENIENT_OPTION_PARSING, std::move (l));
      }
#else
      static
      symbol_type
      make_LENIENT_OPTION_PARSING (const location_type& l)
      {
        return symbol_type (token::TOKEN_LENIENT_OPTION_PARSING, l);
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
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOLEAN (bool v, location_type l)
      {
        return symbol_type (token::TOKEN_BOOLEAN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOLEAN (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOLEAN, v, l);
      }
#endif


    class context
    {
    public:
      context (const Dhcp6Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Dhcp6Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Dhcp6Parser (const Dhcp6Parser&);
    /// Non copyable.
    Dhcp6Parser& operator= (const Dhcp6Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const short yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const short yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const short yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if PARSER6_DEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
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
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

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
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
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
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 1382,     ///< Last index in yytable_.
      yynnts_ = 455,  ///< Number of nonterminal symbols.
      yyfinal_ = 30 ///< Termination state number.
    };


    // User arguments.
    isc::dhcp::Parser6Context& ctx;

  };

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const unsigned char
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
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223
    };
    // Last valid token kind.
    const int code_max = 478;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Dhcp6Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.copy< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.copy< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Dhcp6Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Dhcp6Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Dhcp6Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Dhcp6Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Dhcp6Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Dhcp6Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Dhcp6Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Dhcp6Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5756 "dhcp6_parser.h"




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
