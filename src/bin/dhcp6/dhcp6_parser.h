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
      // ddns_conflict_resolution_mode_value
      // on_fail_mode
      // duid_type
      // control_socket_type_value
      // auth_type_value
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
    TOKEN_USER = 280,              // "user"
    TOKEN_PASSWORD = 281,          // "password"
    TOKEN_HOST = 282,              // "host"
    TOKEN_PORT = 283,              // "port"
    TOKEN_PERSIST = 284,           // "persist"
    TOKEN_LFC_INTERVAL = 285,      // "lfc-interval"
    TOKEN_READONLY = 286,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 287,   // "connect-timeout"
    TOKEN_READ_TIMEOUT = 288,      // "read-timeout"
    TOKEN_WRITE_TIMEOUT = 289,     // "write-timeout"
    TOKEN_TCP_USER_TIMEOUT = 290,  // "tcp-user-timeout"
    TOKEN_MAX_RECONNECT_TRIES = 291, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 292, // "reconnect-wait-time"
    TOKEN_ON_FAIL = 293,           // "on-fail"
    TOKEN_STOP_RETRY_EXIT = 294,   // "stop-retry-exit"
    TOKEN_SERVE_RETRY_EXIT = 295,  // "serve-retry-exit"
    TOKEN_SERVE_RETRY_CONTINUE = 296, // "serve-retry-continue"
    TOKEN_RETRY_ON_STARTUP = 297,  // "retry-on-startup"
    TOKEN_MAX_ROW_ERRORS = 298,    // "max-row-errors"
    TOKEN_TRUST_ANCHOR = 299,      // "trust-anchor"
    TOKEN_CERT_FILE = 300,         // "cert-file"
    TOKEN_KEY_FILE = 301,          // "key-file"
    TOKEN_CIPHER_LIST = 302,       // "cipher-list"
    TOKEN_PREFERRED_LIFETIME = 303, // "preferred-lifetime"
    TOKEN_MIN_PREFERRED_LIFETIME = 304, // "min-preferred-lifetime"
    TOKEN_MAX_PREFERRED_LIFETIME = 305, // "max-preferred-lifetime"
    TOKEN_VALID_LIFETIME = 306,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 307, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 308, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 309,       // "renew-timer"
    TOKEN_REBIND_TIMER = 310,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 311, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 312,        // "t1-percent"
    TOKEN_T2_PERCENT = 313,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 314,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 315,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 316, // "decline-probation-period"
    TOKEN_SERVER_TAG = 317,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 318, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 319, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 320, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 321, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 322, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 323, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 324, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 325, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 326, // "ddns-update-on-renew"
    TOKEN_DDNS_USE_CONFLICT_RESOLUTION = 327, // "ddns-use-conflict-resolution"
    TOKEN_DDNS_TTL_PERCENT = 328,  // "ddns-ttl-percent"
    TOKEN_STORE_EXTENDED_INFO = 329, // "store-extended-info"
    TOKEN_SUBNET6 = 330,           // "subnet6"
    TOKEN_OPTION_DEF = 331,        // "option-def"
    TOKEN_OPTION_DATA = 332,       // "option-data"
    TOKEN_NAME = 333,              // "name"
    TOKEN_DATA = 334,              // "data"
    TOKEN_CODE = 335,              // "code"
    TOKEN_SPACE = 336,             // "space"
    TOKEN_CSV_FORMAT = 337,        // "csv-format"
    TOKEN_ALWAYS_SEND = 338,       // "always-send"
    TOKEN_NEVER_SEND = 339,        // "never-send"
    TOKEN_RECORD_TYPES = 340,      // "record-types"
    TOKEN_ENCAPSULATE = 341,       // "encapsulate"
    TOKEN_ARRAY = 342,             // "array"
    TOKEN_PARKED_PACKET_LIMIT = 343, // "parked-packet-limit"
    TOKEN_ALLOCATOR = 344,         // "allocator"
    TOKEN_PD_ALLOCATOR = 345,      // "pd-allocator"
    TOKEN_DDNS_CONFLICT_RESOLUTION_MODE = 346, // "ddns-conflict-resolution-mode"
    TOKEN_CHECK_WITH_DHCID = 347,  // "check-with-dhcid"
    TOKEN_NO_CHECK_WITH_DHCID = 348, // "no-check-with-dhcid"
    TOKEN_CHECK_EXISTS_WITH_DHCID = 349, // "check-exists-with-dhcid"
    TOKEN_NO_CHECK_WITHOUT_DHCID = 350, // "no-check-without-dhcid"
    TOKEN_SHARED_NETWORKS = 351,   // "shared-networks"
    TOKEN_POOLS = 352,             // "pools"
    TOKEN_POOL = 353,              // "pool"
    TOKEN_PD_POOLS = 354,          // "pd-pools"
    TOKEN_PREFIX = 355,            // "prefix"
    TOKEN_PREFIX_LEN = 356,        // "prefix-len"
    TOKEN_EXCLUDED_PREFIX = 357,   // "excluded-prefix"
    TOKEN_EXCLUDED_PREFIX_LEN = 358, // "excluded-prefix-len"
    TOKEN_DELEGATED_LEN = 359,     // "delegated-len"
    TOKEN_USER_CONTEXT = 360,      // "user-context"
    TOKEN_COMMENT = 361,           // "comment"
    TOKEN_SUBNET = 362,            // "subnet"
    TOKEN_INTERFACE = 363,         // "interface"
    TOKEN_INTERFACE_ID = 364,      // "interface-id"
    TOKEN_ID = 365,                // "id"
    TOKEN_RAPID_COMMIT = 366,      // "rapid-commit"
    TOKEN_RESERVATIONS_GLOBAL = 367, // "reservations-global"
    TOKEN_RESERVATIONS_IN_SUBNET = 368, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 369, // "reservations-out-of-pool"
    TOKEN_MAC_SOURCES = 370,       // "mac-sources"
    TOKEN_RELAY_SUPPLIED_OPTIONS = 371, // "relay-supplied-options"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 372, // "host-reservation-identifiers"
    TOKEN_SANITY_CHECKS = 373,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 374,      // "lease-checks"
    TOKEN_EXTENDED_INFO_CHECKS = 375, // "extended-info-checks"
    TOKEN_CLIENT_CLASSES = 376,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 377, // "require-client-classes"
    TOKEN_EVALUATE_ADDITIONAL_CLASSES = 378, // "evaluate-additional-classes"
    TOKEN_TEST = 379,              // "test"
    TOKEN_TEMPLATE_TEST = 380,     // "template-test"
    TOKEN_ONLY_IF_REQUIRED = 381,  // "only-if-required"
    TOKEN_ONLY_IN_ADDITIONAL_LIST = 382, // "only-in-additional-list"
    TOKEN_CLIENT_CLASS = 383,      // "client-class"
    TOKEN_POOL_ID = 384,           // "pool-id"
    TOKEN_RESERVATIONS = 385,      // "reservations"
    TOKEN_IP_ADDRESSES = 386,      // "ip-addresses"
    TOKEN_PREFIXES = 387,          // "prefixes"
    TOKEN_EXCLUDED_PREFIXES = 388, // "excluded-prefixes"
    TOKEN_DUID = 389,              // "duid"
    TOKEN_HW_ADDRESS = 390,        // "hw-address"
    TOKEN_HOSTNAME = 391,          // "hostname"
    TOKEN_FLEX_ID = 392,           // "flex-id"
    TOKEN_RELAY = 393,             // "relay"
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
    TOKEN_CONTROL_SOCKETS = 418,   // "control-sockets"
    TOKEN_SOCKET_TYPE = 419,       // "socket-type"
    TOKEN_UNIX = 420,              // "unix"
    TOKEN_HTTP = 421,              // "http"
    TOKEN_HTTPS = 422,             // "https"
    TOKEN_SOCKET_NAME = 423,       // "socket-name"
    TOKEN_SOCKET_ADDRESS = 424,    // "socket-address"
    TOKEN_SOCKET_PORT = 425,       // "socket-port"
    TOKEN_AUTHENTICATION = 426,    // "authentication"
    TOKEN_BASIC = 427,             // "basic"
    TOKEN_REALM = 428,             // "realm"
    TOKEN_DIRECTORY = 429,         // "directory"
    TOKEN_CLIENTS = 430,           // "clients"
    TOKEN_USER_FILE = 431,         // "user-file"
    TOKEN_PASSWORD_FILE = 432,     // "password-file"
    TOKEN_CERT_REQUIRED = 433,     // "cert-required"
    TOKEN_HTTP_HEADERS = 434,      // "http-headers"
    TOKEN_VALUE = 435,             // "value"
    TOKEN_DHCP_QUEUE_CONTROL = 436, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 437,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 438,        // "queue-type"
    TOKEN_CAPACITY = 439,          // "capacity"
    TOKEN_DHCP_DDNS = 440,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 441,    // "enable-updates"
    TOKEN_SERVER_IP = 442,         // "server-ip"
    TOKEN_SERVER_PORT = 443,       // "server-port"
    TOKEN_SENDER_IP = 444,         // "sender-ip"
    TOKEN_SENDER_PORT = 445,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 446,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 447,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 448,        // "ncr-format"
    TOKEN_UDP = 449,               // "UDP"
    TOKEN_TCP = 450,               // "TCP"
    TOKEN_JSON = 451,              // "JSON"
    TOKEN_WHEN_PRESENT = 452,      // "when-present"
    TOKEN_NEVER = 453,             // "never"
    TOKEN_ALWAYS = 454,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 455,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 456, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 457, // "hostname-char-replacement"
    TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 458, // "early-global-reservations-lookup"
    TOKEN_IP_RESERVATIONS_UNIQUE = 459, // "ip-reservations-unique"
    TOKEN_RESERVATIONS_LOOKUP_FIRST = 460, // "reservations-lookup-first"
    TOKEN_LOGGERS = 461,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 462,    // "output-options"
    TOKEN_OUTPUT = 463,            // "output"
    TOKEN_DEBUGLEVEL = 464,        // "debuglevel"
    TOKEN_SEVERITY = 465,          // "severity"
    TOKEN_FLUSH = 466,             // "flush"
    TOKEN_MAXSIZE = 467,           // "maxsize"
    TOKEN_MAXVER = 468,            // "maxver"
    TOKEN_PATTERN = 469,           // "pattern"
    TOKEN_COMPATIBILITY = 470,     // "compatibility"
    TOKEN_LENIENT_OPTION_PARSING = 471, // "lenient-option-parsing"
    TOKEN_TOPLEVEL_JSON = 472,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP6 = 473,    // TOPLEVEL_DHCP6
    TOKEN_SUB_DHCP6 = 474,         // SUB_DHCP6
    TOKEN_SUB_INTERFACES6 = 475,   // SUB_INTERFACES6
    TOKEN_SUB_SUBNET6 = 476,       // SUB_SUBNET6
    TOKEN_SUB_POOL6 = 477,         // SUB_POOL6
    TOKEN_SUB_PD_POOL = 478,       // SUB_PD_POOL
    TOKEN_SUB_RESERVATION = 479,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 480,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 481,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 482,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 483, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 484,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 485, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 486,            // "constant string"
    TOKEN_INTEGER = 487,           // "integer"
    TOKEN_FLOAT = 488,             // "floating point"
    TOKEN_BOOLEAN = 489            // "boolean"
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
        YYNTOKENS = 235, ///< Number of tokens.
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
        S_USER = 25,                             // "user"
        S_PASSWORD = 26,                         // "password"
        S_HOST = 27,                             // "host"
        S_PORT = 28,                             // "port"
        S_PERSIST = 29,                          // "persist"
        S_LFC_INTERVAL = 30,                     // "lfc-interval"
        S_READONLY = 31,                         // "readonly"
        S_CONNECT_TIMEOUT = 32,                  // "connect-timeout"
        S_READ_TIMEOUT = 33,                     // "read-timeout"
        S_WRITE_TIMEOUT = 34,                    // "write-timeout"
        S_TCP_USER_TIMEOUT = 35,                 // "tcp-user-timeout"
        S_MAX_RECONNECT_TRIES = 36,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 37,              // "reconnect-wait-time"
        S_ON_FAIL = 38,                          // "on-fail"
        S_STOP_RETRY_EXIT = 39,                  // "stop-retry-exit"
        S_SERVE_RETRY_EXIT = 40,                 // "serve-retry-exit"
        S_SERVE_RETRY_CONTINUE = 41,             // "serve-retry-continue"
        S_RETRY_ON_STARTUP = 42,                 // "retry-on-startup"
        S_MAX_ROW_ERRORS = 43,                   // "max-row-errors"
        S_TRUST_ANCHOR = 44,                     // "trust-anchor"
        S_CERT_FILE = 45,                        // "cert-file"
        S_KEY_FILE = 46,                         // "key-file"
        S_CIPHER_LIST = 47,                      // "cipher-list"
        S_PREFERRED_LIFETIME = 48,               // "preferred-lifetime"
        S_MIN_PREFERRED_LIFETIME = 49,           // "min-preferred-lifetime"
        S_MAX_PREFERRED_LIFETIME = 50,           // "max-preferred-lifetime"
        S_VALID_LIFETIME = 51,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 52,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 53,               // "max-valid-lifetime"
        S_RENEW_TIMER = 54,                      // "renew-timer"
        S_REBIND_TIMER = 55,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 56,              // "calculate-tee-times"
        S_T1_PERCENT = 57,                       // "t1-percent"
        S_T2_PERCENT = 58,                       // "t2-percent"
        S_CACHE_THRESHOLD = 59,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 60,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 61,         // "decline-probation-period"
        S_SERVER_TAG = 62,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 63,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 64,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 65,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 66,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 67,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 68,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 69,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 70,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 71,             // "ddns-update-on-renew"
        S_DDNS_USE_CONFLICT_RESOLUTION = 72,     // "ddns-use-conflict-resolution"
        S_DDNS_TTL_PERCENT = 73,                 // "ddns-ttl-percent"
        S_STORE_EXTENDED_INFO = 74,              // "store-extended-info"
        S_SUBNET6 = 75,                          // "subnet6"
        S_OPTION_DEF = 76,                       // "option-def"
        S_OPTION_DATA = 77,                      // "option-data"
        S_NAME = 78,                             // "name"
        S_DATA = 79,                             // "data"
        S_CODE = 80,                             // "code"
        S_SPACE = 81,                            // "space"
        S_CSV_FORMAT = 82,                       // "csv-format"
        S_ALWAYS_SEND = 83,                      // "always-send"
        S_NEVER_SEND = 84,                       // "never-send"
        S_RECORD_TYPES = 85,                     // "record-types"
        S_ENCAPSULATE = 86,                      // "encapsulate"
        S_ARRAY = 87,                            // "array"
        S_PARKED_PACKET_LIMIT = 88,              // "parked-packet-limit"
        S_ALLOCATOR = 89,                        // "allocator"
        S_PD_ALLOCATOR = 90,                     // "pd-allocator"
        S_DDNS_CONFLICT_RESOLUTION_MODE = 91,    // "ddns-conflict-resolution-mode"
        S_CHECK_WITH_DHCID = 92,                 // "check-with-dhcid"
        S_NO_CHECK_WITH_DHCID = 93,              // "no-check-with-dhcid"
        S_CHECK_EXISTS_WITH_DHCID = 94,          // "check-exists-with-dhcid"
        S_NO_CHECK_WITHOUT_DHCID = 95,           // "no-check-without-dhcid"
        S_SHARED_NETWORKS = 96,                  // "shared-networks"
        S_POOLS = 97,                            // "pools"
        S_POOL = 98,                             // "pool"
        S_PD_POOLS = 99,                         // "pd-pools"
        S_PREFIX = 100,                          // "prefix"
        S_PREFIX_LEN = 101,                      // "prefix-len"
        S_EXCLUDED_PREFIX = 102,                 // "excluded-prefix"
        S_EXCLUDED_PREFIX_LEN = 103,             // "excluded-prefix-len"
        S_DELEGATED_LEN = 104,                   // "delegated-len"
        S_USER_CONTEXT = 105,                    // "user-context"
        S_COMMENT = 106,                         // "comment"
        S_SUBNET = 107,                          // "subnet"
        S_INTERFACE = 108,                       // "interface"
        S_INTERFACE_ID = 109,                    // "interface-id"
        S_ID = 110,                              // "id"
        S_RAPID_COMMIT = 111,                    // "rapid-commit"
        S_RESERVATIONS_GLOBAL = 112,             // "reservations-global"
        S_RESERVATIONS_IN_SUBNET = 113,          // "reservations-in-subnet"
        S_RESERVATIONS_OUT_OF_POOL = 114,        // "reservations-out-of-pool"
        S_MAC_SOURCES = 115,                     // "mac-sources"
        S_RELAY_SUPPLIED_OPTIONS = 116,          // "relay-supplied-options"
        S_HOST_RESERVATION_IDENTIFIERS = 117,    // "host-reservation-identifiers"
        S_SANITY_CHECKS = 118,                   // "sanity-checks"
        S_LEASE_CHECKS = 119,                    // "lease-checks"
        S_EXTENDED_INFO_CHECKS = 120,            // "extended-info-checks"
        S_CLIENT_CLASSES = 121,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 122,          // "require-client-classes"
        S_EVALUATE_ADDITIONAL_CLASSES = 123,     // "evaluate-additional-classes"
        S_TEST = 124,                            // "test"
        S_TEMPLATE_TEST = 125,                   // "template-test"
        S_ONLY_IF_REQUIRED = 126,                // "only-if-required"
        S_ONLY_IN_ADDITIONAL_LIST = 127,         // "only-in-additional-list"
        S_CLIENT_CLASS = 128,                    // "client-class"
        S_POOL_ID = 129,                         // "pool-id"
        S_RESERVATIONS = 130,                    // "reservations"
        S_IP_ADDRESSES = 131,                    // "ip-addresses"
        S_PREFIXES = 132,                        // "prefixes"
        S_EXCLUDED_PREFIXES = 133,               // "excluded-prefixes"
        S_DUID = 134,                            // "duid"
        S_HW_ADDRESS = 135,                      // "hw-address"
        S_HOSTNAME = 136,                        // "hostname"
        S_FLEX_ID = 137,                         // "flex-id"
        S_RELAY = 138,                           // "relay"
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
        S_CONTROL_SOCKETS = 163,                 // "control-sockets"
        S_SOCKET_TYPE = 164,                     // "socket-type"
        S_UNIX = 165,                            // "unix"
        S_HTTP = 166,                            // "http"
        S_HTTPS = 167,                           // "https"
        S_SOCKET_NAME = 168,                     // "socket-name"
        S_SOCKET_ADDRESS = 169,                  // "socket-address"
        S_SOCKET_PORT = 170,                     // "socket-port"
        S_AUTHENTICATION = 171,                  // "authentication"
        S_BASIC = 172,                           // "basic"
        S_REALM = 173,                           // "realm"
        S_DIRECTORY = 174,                       // "directory"
        S_CLIENTS = 175,                         // "clients"
        S_USER_FILE = 176,                       // "user-file"
        S_PASSWORD_FILE = 177,                   // "password-file"
        S_CERT_REQUIRED = 178,                   // "cert-required"
        S_HTTP_HEADERS = 179,                    // "http-headers"
        S_VALUE = 180,                           // "value"
        S_DHCP_QUEUE_CONTROL = 181,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 182,                    // "enable-queue"
        S_QUEUE_TYPE = 183,                      // "queue-type"
        S_CAPACITY = 184,                        // "capacity"
        S_DHCP_DDNS = 185,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 186,                  // "enable-updates"
        S_SERVER_IP = 187,                       // "server-ip"
        S_SERVER_PORT = 188,                     // "server-port"
        S_SENDER_IP = 189,                       // "sender-ip"
        S_SENDER_PORT = 190,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 191,                  // "max-queue-size"
        S_NCR_PROTOCOL = 192,                    // "ncr-protocol"
        S_NCR_FORMAT = 193,                      // "ncr-format"
        S_UDP = 194,                             // "UDP"
        S_TCP = 195,                             // "TCP"
        S_JSON = 196,                            // "JSON"
        S_WHEN_PRESENT = 197,                    // "when-present"
        S_NEVER = 198,                           // "never"
        S_ALWAYS = 199,                          // "always"
        S_WHEN_NOT_PRESENT = 200,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 201,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 202,       // "hostname-char-replacement"
        S_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 203, // "early-global-reservations-lookup"
        S_IP_RESERVATIONS_UNIQUE = 204,          // "ip-reservations-unique"
        S_RESERVATIONS_LOOKUP_FIRST = 205,       // "reservations-lookup-first"
        S_LOGGERS = 206,                         // "loggers"
        S_OUTPUT_OPTIONS = 207,                  // "output-options"
        S_OUTPUT = 208,                          // "output"
        S_DEBUGLEVEL = 209,                      // "debuglevel"
        S_SEVERITY = 210,                        // "severity"
        S_FLUSH = 211,                           // "flush"
        S_MAXSIZE = 212,                         // "maxsize"
        S_MAXVER = 213,                          // "maxver"
        S_PATTERN = 214,                         // "pattern"
        S_COMPATIBILITY = 215,                   // "compatibility"
        S_LENIENT_OPTION_PARSING = 216,          // "lenient-option-parsing"
        S_TOPLEVEL_JSON = 217,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP6 = 218,                  // TOPLEVEL_DHCP6
        S_SUB_DHCP6 = 219,                       // SUB_DHCP6
        S_SUB_INTERFACES6 = 220,                 // SUB_INTERFACES6
        S_SUB_SUBNET6 = 221,                     // SUB_SUBNET6
        S_SUB_POOL6 = 222,                       // SUB_POOL6
        S_SUB_PD_POOL = 223,                     // SUB_PD_POOL
        S_SUB_RESERVATION = 224,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 225,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 226,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 227,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 228,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 229,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 230,              // SUB_CONFIG_CONTROL
        S_STRING = 231,                          // "constant string"
        S_INTEGER = 232,                         // "integer"
        S_FLOAT = 233,                           // "floating point"
        S_BOOLEAN = 234,                         // "boolean"
        S_YYACCEPT = 235,                        // $accept
        S_start = 236,                           // start
        S_237_1 = 237,                           // $@1
        S_238_2 = 238,                           // $@2
        S_239_3 = 239,                           // $@3
        S_240_4 = 240,                           // $@4
        S_241_5 = 241,                           // $@5
        S_242_6 = 242,                           // $@6
        S_243_7 = 243,                           // $@7
        S_244_8 = 244,                           // $@8
        S_245_9 = 245,                           // $@9
        S_246_10 = 246,                          // $@10
        S_247_11 = 247,                          // $@11
        S_248_12 = 248,                          // $@12
        S_249_13 = 249,                          // $@13
        S_250_14 = 250,                          // $@14
        S_value = 251,                           // value
        S_sub_json = 252,                        // sub_json
        S_map2 = 253,                            // map2
        S_254_15 = 254,                          // $@15
        S_map_value = 255,                       // map_value
        S_map_content = 256,                     // map_content
        S_not_empty_map = 257,                   // not_empty_map
        S_list_generic = 258,                    // list_generic
        S_259_16 = 259,                          // $@16
        S_list_content = 260,                    // list_content
        S_not_empty_list = 261,                  // not_empty_list
        S_list_strings = 262,                    // list_strings
        S_263_17 = 263,                          // $@17
        S_list_strings_content = 264,            // list_strings_content
        S_not_empty_list_strings = 265,          // not_empty_list_strings
        S_unknown_map_entry = 266,               // unknown_map_entry
        S_syntax_map = 267,                      // syntax_map
        S_268_18 = 268,                          // $@18
        S_global_object = 269,                   // global_object
        S_270_19 = 270,                          // $@19
        S_global_object_comma = 271,             // global_object_comma
        S_sub_dhcp6 = 272,                       // sub_dhcp6
        S_273_20 = 273,                          // $@20
        S_global_params = 274,                   // global_params
        S_global_param = 275,                    // global_param
        S_data_directory = 276,                  // data_directory
        S_277_21 = 277,                          // $@21
        S_preferred_lifetime = 278,              // preferred_lifetime
        S_min_preferred_lifetime = 279,          // min_preferred_lifetime
        S_max_preferred_lifetime = 280,          // max_preferred_lifetime
        S_valid_lifetime = 281,                  // valid_lifetime
        S_min_valid_lifetime = 282,              // min_valid_lifetime
        S_max_valid_lifetime = 283,              // max_valid_lifetime
        S_renew_timer = 284,                     // renew_timer
        S_rebind_timer = 285,                    // rebind_timer
        S_calculate_tee_times = 286,             // calculate_tee_times
        S_t1_percent = 287,                      // t1_percent
        S_t2_percent = 288,                      // t2_percent
        S_cache_threshold = 289,                 // cache_threshold
        S_cache_max_age = 290,                   // cache_max_age
        S_decline_probation_period = 291,        // decline_probation_period
        S_ddns_send_updates = 292,               // ddns_send_updates
        S_ddns_override_no_update = 293,         // ddns_override_no_update
        S_ddns_override_client_update = 294,     // ddns_override_client_update
        S_ddns_replace_client_name = 295,        // ddns_replace_client_name
        S_296_22 = 296,                          // $@22
        S_ddns_replace_client_name_value = 297,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 298,           // ddns_generated_prefix
        S_299_23 = 299,                          // $@23
        S_ddns_qualifying_suffix = 300,          // ddns_qualifying_suffix
        S_301_24 = 301,                          // $@24
        S_ddns_update_on_renew = 302,            // ddns_update_on_renew
        S_ddns_use_conflict_resolution = 303,    // ddns_use_conflict_resolution
        S_ddns_conflict_resolution_mode = 304,   // ddns_conflict_resolution_mode
        S_305_25 = 305,                          // $@25
        S_ddns_conflict_resolution_mode_value = 306, // ddns_conflict_resolution_mode_value
        S_ddns_ttl_percent = 307,                // ddns_ttl_percent
        S_hostname_char_set = 308,               // hostname_char_set
        S_309_26 = 309,                          // $@26
        S_hostname_char_replacement = 310,       // hostname_char_replacement
        S_311_27 = 311,                          // $@27
        S_store_extended_info = 312,             // store_extended_info
        S_statistic_default_sample_count = 313,  // statistic_default_sample_count
        S_statistic_default_sample_age = 314,    // statistic_default_sample_age
        S_server_tag = 315,                      // server_tag
        S_316_28 = 316,                          // $@28
        S_parked_packet_limit = 317,             // parked_packet_limit
        S_allocator = 318,                       // allocator
        S_319_29 = 319,                          // $@29
        S_pd_allocator = 320,                    // pd_allocator
        S_321_30 = 321,                          // $@30
        S_early_global_reservations_lookup = 322, // early_global_reservations_lookup
        S_ip_reservations_unique = 323,          // ip_reservations_unique
        S_reservations_lookup_first = 324,       // reservations_lookup_first
        S_interfaces_config = 325,               // interfaces_config
        S_326_31 = 326,                          // $@31
        S_sub_interfaces6 = 327,                 // sub_interfaces6
        S_328_32 = 328,                          // $@32
        S_interfaces_config_params = 329,        // interfaces_config_params
        S_interfaces_config_param = 330,         // interfaces_config_param
        S_interfaces_list = 331,                 // interfaces_list
        S_332_33 = 332,                          // $@33
        S_re_detect = 333,                       // re_detect
        S_service_sockets_require_all = 334,     // service_sockets_require_all
        S_service_sockets_retry_wait_time = 335, // service_sockets_retry_wait_time
        S_service_sockets_max_retries = 336,     // service_sockets_max_retries
        S_lease_database = 337,                  // lease_database
        S_338_34 = 338,                          // $@34
        S_hosts_database = 339,                  // hosts_database
        S_340_35 = 340,                          // $@35
        S_hosts_databases = 341,                 // hosts_databases
        S_342_36 = 342,                          // $@36
        S_database_list = 343,                   // database_list
        S_not_empty_database_list = 344,         // not_empty_database_list
        S_database = 345,                        // database
        S_346_37 = 346,                          // $@37
        S_database_map_params = 347,             // database_map_params
        S_database_map_param = 348,              // database_map_param
        S_database_type = 349,                   // database_type
        S_350_38 = 350,                          // $@38
        S_user = 351,                            // user
        S_352_39 = 352,                          // $@39
        S_password = 353,                        // password
        S_354_40 = 354,                          // $@40
        S_host = 355,                            // host
        S_356_41 = 356,                          // $@41
        S_port = 357,                            // port
        S_name = 358,                            // name
        S_359_42 = 359,                          // $@42
        S_persist = 360,                         // persist
        S_lfc_interval = 361,                    // lfc_interval
        S_readonly = 362,                        // readonly
        S_connect_timeout = 363,                 // connect_timeout
        S_read_timeout = 364,                    // read_timeout
        S_write_timeout = 365,                   // write_timeout
        S_tcp_user_timeout = 366,                // tcp_user_timeout
        S_reconnect_wait_time = 367,             // reconnect_wait_time
        S_on_fail = 368,                         // on_fail
        S_369_43 = 369,                          // $@43
        S_on_fail_mode = 370,                    // on_fail_mode
        S_retry_on_startup = 371,                // retry_on_startup
        S_max_row_errors = 372,                  // max_row_errors
        S_max_reconnect_tries = 373,             // max_reconnect_tries
        S_trust_anchor = 374,                    // trust_anchor
        S_375_44 = 375,                          // $@44
        S_cert_file = 376,                       // cert_file
        S_377_45 = 377,                          // $@45
        S_key_file = 378,                        // key_file
        S_379_46 = 379,                          // $@46
        S_cipher_list = 380,                     // cipher_list
        S_381_47 = 381,                          // $@47
        S_sanity_checks = 382,                   // sanity_checks
        S_383_48 = 383,                          // $@48
        S_sanity_checks_params = 384,            // sanity_checks_params
        S_sanity_checks_param = 385,             // sanity_checks_param
        S_lease_checks = 386,                    // lease_checks
        S_387_49 = 387,                          // $@49
        S_extended_info_checks = 388,            // extended_info_checks
        S_389_50 = 389,                          // $@50
        S_mac_sources = 390,                     // mac_sources
        S_391_51 = 391,                          // $@51
        S_mac_sources_list = 392,                // mac_sources_list
        S_mac_sources_value = 393,               // mac_sources_value
        S_duid_id = 394,                         // duid_id
        S_string_id = 395,                       // string_id
        S_host_reservation_identifiers = 396,    // host_reservation_identifiers
        S_397_52 = 397,                          // $@52
        S_host_reservation_identifiers_list = 398, // host_reservation_identifiers_list
        S_host_reservation_identifier = 399,     // host_reservation_identifier
        S_hw_address_id = 400,                   // hw_address_id
        S_flex_id = 401,                         // flex_id
        S_relay_supplied_options = 402,          // relay_supplied_options
        S_403_53 = 403,                          // $@53
        S_dhcp_multi_threading = 404,            // dhcp_multi_threading
        S_405_54 = 405,                          // $@54
        S_multi_threading_params = 406,          // multi_threading_params
        S_multi_threading_param = 407,           // multi_threading_param
        S_enable_multi_threading = 408,          // enable_multi_threading
        S_thread_pool_size = 409,                // thread_pool_size
        S_packet_queue_size = 410,               // packet_queue_size
        S_hooks_libraries = 411,                 // hooks_libraries
        S_412_55 = 412,                          // $@55
        S_hooks_libraries_list = 413,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 414,  // not_empty_hooks_libraries_list
        S_hooks_library = 415,                   // hooks_library
        S_416_56 = 416,                          // $@56
        S_sub_hooks_library = 417,               // sub_hooks_library
        S_418_57 = 418,                          // $@57
        S_hooks_params = 419,                    // hooks_params
        S_hooks_param = 420,                     // hooks_param
        S_library = 421,                         // library
        S_422_58 = 422,                          // $@58
        S_parameters = 423,                      // parameters
        S_424_59 = 424,                          // $@59
        S_expired_leases_processing = 425,       // expired_leases_processing
        S_426_60 = 426,                          // $@60
        S_expired_leases_params = 427,           // expired_leases_params
        S_expired_leases_param = 428,            // expired_leases_param
        S_reclaim_timer_wait_time = 429,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 430, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 431,             // hold_reclaimed_time
        S_max_reclaim_leases = 432,              // max_reclaim_leases
        S_max_reclaim_time = 433,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 434,         // unwarned_reclaim_cycles
        S_subnet6_list = 435,                    // subnet6_list
        S_436_61 = 436,                          // $@61
        S_subnet6_list_content = 437,            // subnet6_list_content
        S_not_empty_subnet6_list = 438,          // not_empty_subnet6_list
        S_subnet6 = 439,                         // subnet6
        S_440_62 = 440,                          // $@62
        S_sub_subnet6 = 441,                     // sub_subnet6
        S_442_63 = 442,                          // $@63
        S_subnet6_params = 443,                  // subnet6_params
        S_subnet6_param = 444,                   // subnet6_param
        S_subnet = 445,                          // subnet
        S_446_64 = 446,                          // $@64
        S_interface = 447,                       // interface
        S_448_65 = 448,                          // $@65
        S_interface_id = 449,                    // interface_id
        S_450_66 = 450,                          // $@66
        S_client_class = 451,                    // client_class
        S_452_67 = 452,                          // $@67
        S_require_client_classes = 453,          // require_client_classes
        S_454_68 = 454,                          // $@68
        S_evaluate_additional_classes = 455,     // evaluate_additional_classes
        S_456_69 = 456,                          // $@69
        S_reservations_global = 457,             // reservations_global
        S_reservations_in_subnet = 458,          // reservations_in_subnet
        S_reservations_out_of_pool = 459,        // reservations_out_of_pool
        S_id = 460,                              // id
        S_rapid_commit = 461,                    // rapid_commit
        S_shared_networks = 462,                 // shared_networks
        S_463_70 = 463,                          // $@70
        S_shared_networks_content = 464,         // shared_networks_content
        S_shared_networks_list = 465,            // shared_networks_list
        S_shared_network = 466,                  // shared_network
        S_467_71 = 467,                          // $@71
        S_shared_network_params = 468,           // shared_network_params
        S_shared_network_param = 469,            // shared_network_param
        S_option_def_list = 470,                 // option_def_list
        S_471_72 = 471,                          // $@72
        S_sub_option_def_list = 472,             // sub_option_def_list
        S_473_73 = 473,                          // $@73
        S_option_def_list_content = 474,         // option_def_list_content
        S_not_empty_option_def_list = 475,       // not_empty_option_def_list
        S_option_def_entry = 476,                // option_def_entry
        S_477_74 = 477,                          // $@74
        S_sub_option_def = 478,                  // sub_option_def
        S_479_75 = 479,                          // $@75
        S_option_def_params = 480,               // option_def_params
        S_not_empty_option_def_params = 481,     // not_empty_option_def_params
        S_option_def_param = 482,                // option_def_param
        S_option_def_name = 483,                 // option_def_name
        S_code = 484,                            // code
        S_option_def_code = 485,                 // option_def_code
        S_option_def_type = 486,                 // option_def_type
        S_487_76 = 487,                          // $@76
        S_option_def_record_types = 488,         // option_def_record_types
        S_489_77 = 489,                          // $@77
        S_space = 490,                           // space
        S_491_78 = 491,                          // $@78
        S_option_def_space = 492,                // option_def_space
        S_option_def_encapsulate = 493,          // option_def_encapsulate
        S_494_79 = 494,                          // $@79
        S_option_def_array = 495,                // option_def_array
        S_option_data_list = 496,                // option_data_list
        S_497_80 = 497,                          // $@80
        S_option_data_list_content = 498,        // option_data_list_content
        S_not_empty_option_data_list = 499,      // not_empty_option_data_list
        S_option_data_entry = 500,               // option_data_entry
        S_501_81 = 501,                          // $@81
        S_sub_option_data = 502,                 // sub_option_data
        S_503_82 = 503,                          // $@82
        S_option_data_params = 504,              // option_data_params
        S_not_empty_option_data_params = 505,    // not_empty_option_data_params
        S_option_data_param = 506,               // option_data_param
        S_option_data_name = 507,                // option_data_name
        S_option_data_data = 508,                // option_data_data
        S_509_83 = 509,                          // $@83
        S_option_data_code = 510,                // option_data_code
        S_option_data_space = 511,               // option_data_space
        S_option_data_csv_format = 512,          // option_data_csv_format
        S_option_data_always_send = 513,         // option_data_always_send
        S_option_data_never_send = 514,          // option_data_never_send
        S_option_data_client_classes = 515,      // option_data_client_classes
        S_516_84 = 516,                          // $@84
        S_pools_list = 517,                      // pools_list
        S_518_85 = 518,                          // $@85
        S_pools_list_content = 519,              // pools_list_content
        S_not_empty_pools_list = 520,            // not_empty_pools_list
        S_pool_list_entry = 521,                 // pool_list_entry
        S_522_86 = 522,                          // $@86
        S_sub_pool6 = 523,                       // sub_pool6
        S_524_87 = 524,                          // $@87
        S_pool_params = 525,                     // pool_params
        S_pool_param = 526,                      // pool_param
        S_pool_entry = 527,                      // pool_entry
        S_528_88 = 528,                          // $@88
        S_pool_id = 529,                         // pool_id
        S_user_context = 530,                    // user_context
        S_531_89 = 531,                          // $@89
        S_comment = 532,                         // comment
        S_533_90 = 533,                          // $@90
        S_pd_pools_list = 534,                   // pd_pools_list
        S_535_91 = 535,                          // $@91
        S_pd_pools_list_content = 536,           // pd_pools_list_content
        S_not_empty_pd_pools_list = 537,         // not_empty_pd_pools_list
        S_pd_pool_entry = 538,                   // pd_pool_entry
        S_539_92 = 539,                          // $@92
        S_sub_pd_pool = 540,                     // sub_pd_pool
        S_541_93 = 541,                          // $@93
        S_pd_pool_params = 542,                  // pd_pool_params
        S_pd_pool_param = 543,                   // pd_pool_param
        S_pd_prefix = 544,                       // pd_prefix
        S_545_94 = 545,                          // $@94
        S_pd_prefix_len = 546,                   // pd_prefix_len
        S_excluded_prefix = 547,                 // excluded_prefix
        S_548_95 = 548,                          // $@95
        S_excluded_prefix_len = 549,             // excluded_prefix_len
        S_pd_delegated_len = 550,                // pd_delegated_len
        S_reservations = 551,                    // reservations
        S_552_96 = 552,                          // $@96
        S_reservations_list = 553,               // reservations_list
        S_not_empty_reservations_list = 554,     // not_empty_reservations_list
        S_reservation = 555,                     // reservation
        S_556_97 = 556,                          // $@97
        S_sub_reservation = 557,                 // sub_reservation
        S_558_98 = 558,                          // $@98
        S_reservation_params = 559,              // reservation_params
        S_not_empty_reservation_params = 560,    // not_empty_reservation_params
        S_reservation_param = 561,               // reservation_param
        S_ip_addresses = 562,                    // ip_addresses
        S_563_99 = 563,                          // $@99
        S_prefixes = 564,                        // prefixes
        S_565_100 = 565,                         // $@100
        S_excluded_prefixes = 566,               // excluded_prefixes
        S_567_101 = 567,                         // $@101
        S_duid = 568,                            // duid
        S_569_102 = 569,                         // $@102
        S_hw_address = 570,                      // hw_address
        S_571_103 = 571,                         // $@103
        S_hostname = 572,                        // hostname
        S_573_104 = 573,                         // $@104
        S_flex_id_value = 574,                   // flex_id_value
        S_575_105 = 575,                         // $@105
        S_reservation_client_classes = 576,      // reservation_client_classes
        S_577_106 = 577,                         // $@106
        S_relay = 578,                           // relay
        S_579_107 = 579,                         // $@107
        S_relay_map = 580,                       // relay_map
        S_client_classes = 581,                  // client_classes
        S_582_108 = 582,                         // $@108
        S_client_classes_list = 583,             // client_classes_list
        S_client_class_entry = 584,              // client_class_entry
        S_585_109 = 585,                         // $@109
        S_client_class_params = 586,             // client_class_params
        S_not_empty_client_class_params = 587,   // not_empty_client_class_params
        S_client_class_param = 588,              // client_class_param
        S_client_class_name = 589,               // client_class_name
        S_client_class_test = 590,               // client_class_test
        S_591_110 = 591,                         // $@110
        S_client_class_template_test = 592,      // client_class_template_test
        S_593_111 = 593,                         // $@111
        S_only_if_required = 594,                // only_if_required
        S_only_in_additional_list = 595,         // only_in_additional_list
        S_server_id = 596,                       // server_id
        S_597_112 = 597,                         // $@112
        S_server_id_params = 598,                // server_id_params
        S_server_id_param = 599,                 // server_id_param
        S_server_id_type = 600,                  // server_id_type
        S_601_113 = 601,                         // $@113
        S_duid_type = 602,                       // duid_type
        S_htype = 603,                           // htype
        S_identifier = 604,                      // identifier
        S_605_114 = 605,                         // $@114
        S_time = 606,                            // time
        S_enterprise_id = 607,                   // enterprise_id
        S_dhcp4o6_port = 608,                    // dhcp4o6_port
        S_control_socket = 609,                  // control_socket
        S_610_115 = 610,                         // $@115
        S_control_sockets = 611,                 // control_sockets
        S_612_116 = 612,                         // $@116
        S_control_socket_list = 613,             // control_socket_list
        S_not_empty_control_socket_list = 614,   // not_empty_control_socket_list
        S_control_socket_entry = 615,            // control_socket_entry
        S_616_117 = 616,                         // $@117
        S_control_socket_params = 617,           // control_socket_params
        S_control_socket_param = 618,            // control_socket_param
        S_control_socket_type = 619,             // control_socket_type
        S_620_118 = 620,                         // $@118
        S_control_socket_type_value = 621,       // control_socket_type_value
        S_control_socket_name = 622,             // control_socket_name
        S_623_119 = 623,                         // $@119
        S_control_socket_address = 624,          // control_socket_address
        S_625_120 = 625,                         // $@120
        S_control_socket_port = 626,             // control_socket_port
        S_cert_required = 627,                   // cert_required
        S_http_headers = 628,                    // http_headers
        S_629_121 = 629,                         // $@121
        S_http_header_list = 630,                // http_header_list
        S_not_empty_http_header_list = 631,      // not_empty_http_header_list
        S_http_header = 632,                     // http_header
        S_633_122 = 633,                         // $@122
        S_http_header_params = 634,              // http_header_params
        S_http_header_param = 635,               // http_header_param
        S_636_123 = 636,                         // $@123
        S_authentication = 637,                  // authentication
        S_638_124 = 638,                         // $@124
        S_auth_params = 639,                     // auth_params
        S_auth_param = 640,                      // auth_param
        S_auth_type = 641,                       // auth_type
        S_642_125 = 642,                         // $@125
        S_auth_type_value = 643,                 // auth_type_value
        S_realm = 644,                           // realm
        S_645_126 = 645,                         // $@126
        S_directory = 646,                       // directory
        S_647_127 = 647,                         // $@127
        S_clients = 648,                         // clients
        S_649_128 = 649,                         // $@128
        S_clients_list = 650,                    // clients_list
        S_not_empty_clients_list = 651,          // not_empty_clients_list
        S_basic_auth = 652,                      // basic_auth
        S_653_129 = 653,                         // $@129
        S_clients_params = 654,                  // clients_params
        S_clients_param = 655,                   // clients_param
        S_user_file = 656,                       // user_file
        S_657_130 = 657,                         // $@130
        S_password_file = 658,                   // password_file
        S_659_131 = 659,                         // $@131
        S_dhcp_queue_control = 660,              // dhcp_queue_control
        S_661_132 = 661,                         // $@132
        S_queue_control_params = 662,            // queue_control_params
        S_queue_control_param = 663,             // queue_control_param
        S_enable_queue = 664,                    // enable_queue
        S_queue_type = 665,                      // queue_type
        S_666_133 = 666,                         // $@133
        S_capacity = 667,                        // capacity
        S_arbitrary_map_entry = 668,             // arbitrary_map_entry
        S_669_134 = 669,                         // $@134
        S_dhcp_ddns = 670,                       // dhcp_ddns
        S_671_135 = 671,                         // $@135
        S_sub_dhcp_ddns = 672,                   // sub_dhcp_ddns
        S_673_136 = 673,                         // $@136
        S_dhcp_ddns_params = 674,                // dhcp_ddns_params
        S_dhcp_ddns_param = 675,                 // dhcp_ddns_param
        S_enable_updates = 676,                  // enable_updates
        S_server_ip = 677,                       // server_ip
        S_678_137 = 678,                         // $@137
        S_server_port = 679,                     // server_port
        S_sender_ip = 680,                       // sender_ip
        S_681_138 = 681,                         // $@138
        S_sender_port = 682,                     // sender_port
        S_max_queue_size = 683,                  // max_queue_size
        S_ncr_protocol = 684,                    // ncr_protocol
        S_685_139 = 685,                         // $@139
        S_ncr_protocol_value = 686,              // ncr_protocol_value
        S_ncr_format = 687,                      // ncr_format
        S_688_140 = 688,                         // $@140
        S_config_control = 689,                  // config_control
        S_690_141 = 690,                         // $@141
        S_sub_config_control = 691,              // sub_config_control
        S_692_142 = 692,                         // $@142
        S_config_control_params = 693,           // config_control_params
        S_config_control_param = 694,            // config_control_param
        S_config_databases = 695,                // config_databases
        S_696_143 = 696,                         // $@143
        S_config_fetch_wait_time = 697,          // config_fetch_wait_time
        S_loggers = 698,                         // loggers
        S_699_144 = 699,                         // $@144
        S_loggers_entries = 700,                 // loggers_entries
        S_logger_entry = 701,                    // logger_entry
        S_702_145 = 702,                         // $@145
        S_logger_params = 703,                   // logger_params
        S_logger_param = 704,                    // logger_param
        S_debuglevel = 705,                      // debuglevel
        S_severity = 706,                        // severity
        S_707_146 = 707,                         // $@146
        S_output_options_list = 708,             // output_options_list
        S_709_147 = 709,                         // $@147
        S_output_options_list_content = 710,     // output_options_list_content
        S_output_entry = 711,                    // output_entry
        S_712_148 = 712,                         // $@148
        S_output_params_list = 713,              // output_params_list
        S_output_params = 714,                   // output_params
        S_output = 715,                          // output
        S_716_149 = 716,                         // $@149
        S_flush = 717,                           // flush
        S_maxsize = 718,                         // maxsize
        S_maxver = 719,                          // maxver
        S_pattern = 720,                         // pattern
        S_721_150 = 721,                         // $@150
        S_compatibility = 722,                   // compatibility
        S_723_151 = 723,                         // $@151
        S_compatibility_params = 724,            // compatibility_params
        S_compatibility_param = 725,             // compatibility_param
        S_lenient_option_parsing = 726           // lenient_option_parsing
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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      make_RETRY_ON_STARTUP (location_type l)
      {
        return symbol_type (token::TOKEN_RETRY_ON_STARTUP, std::move (l));
      }
#else
      static
      symbol_type
      make_RETRY_ON_STARTUP (const location_type& l)
      {
        return symbol_type (token::TOKEN_RETRY_ON_STARTUP, l);
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
      make_DDNS_CONFLICT_RESOLUTION_MODE (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_CONFLICT_RESOLUTION_MODE, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_CONFLICT_RESOLUTION_MODE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_CONFLICT_RESOLUTION_MODE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHECK_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_CHECK_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NO_CHECK_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_NO_CHECK_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHECK_EXISTS_WITH_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_EXISTS_WITH_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_CHECK_EXISTS_WITH_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_EXISTS_WITH_DHCID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NO_CHECK_WITHOUT_DHCID (location_type l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITHOUT_DHCID, std::move (l));
      }
#else
      static
      symbol_type
      make_NO_CHECK_WITHOUT_DHCID (const location_type& l)
      {
        return symbol_type (token::TOKEN_NO_CHECK_WITHOUT_DHCID, l);
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
      make_EVALUATE_ADDITIONAL_CLASSES (location_type l)
      {
        return symbol_type (token::TOKEN_EVALUATE_ADDITIONAL_CLASSES, std::move (l));
      }
#else
      static
      symbol_type
      make_EVALUATE_ADDITIONAL_CLASSES (const location_type& l)
      {
        return symbol_type (token::TOKEN_EVALUATE_ADDITIONAL_CLASSES, l);
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
      make_ONLY_IN_ADDITIONAL_LIST (location_type l)
      {
        return symbol_type (token::TOKEN_ONLY_IN_ADDITIONAL_LIST, std::move (l));
      }
#else
      static
      symbol_type
      make_ONLY_IN_ADDITIONAL_LIST (const location_type& l)
      {
        return symbol_type (token::TOKEN_ONLY_IN_ADDITIONAL_LIST, l);
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
      make_EXCLUDED_PREFIXES (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIXES, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDED_PREFIXES (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDED_PREFIXES, l);
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
      make_CONTROL_SOCKETS (location_type l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKETS, std::move (l));
      }
#else
      static
      symbol_type
      make_CONTROL_SOCKETS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONTROL_SOCKETS, l);
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
      make_UNIX (location_type l)
      {
        return symbol_type (token::TOKEN_UNIX, std::move (l));
      }
#else
      static
      symbol_type
      make_UNIX (const location_type& l)
      {
        return symbol_type (token::TOKEN_UNIX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTP (location_type l)
      {
        return symbol_type (token::TOKEN_HTTP, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTP (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTPS (location_type l)
      {
        return symbol_type (token::TOKEN_HTTPS, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTPS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTPS, l);
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
      make_SOCKET_ADDRESS (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_ADDRESS, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_ADDRESS (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_ADDRESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SOCKET_PORT (location_type l)
      {
        return symbol_type (token::TOKEN_SOCKET_PORT, std::move (l));
      }
#else
      static
      symbol_type
      make_SOCKET_PORT (const location_type& l)
      {
        return symbol_type (token::TOKEN_SOCKET_PORT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTHENTICATION (location_type l)
      {
        return symbol_type (token::TOKEN_AUTHENTICATION, std::move (l));
      }
#else
      static
      symbol_type
      make_AUTHENTICATION (const location_type& l)
      {
        return symbol_type (token::TOKEN_AUTHENTICATION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BASIC (location_type l)
      {
        return symbol_type (token::TOKEN_BASIC, std::move (l));
      }
#else
      static
      symbol_type
      make_BASIC (const location_type& l)
      {
        return symbol_type (token::TOKEN_BASIC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REALM (location_type l)
      {
        return symbol_type (token::TOKEN_REALM, std::move (l));
      }
#else
      static
      symbol_type
      make_REALM (const location_type& l)
      {
        return symbol_type (token::TOKEN_REALM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIRECTORY (location_type l)
      {
        return symbol_type (token::TOKEN_DIRECTORY, std::move (l));
      }
#else
      static
      symbol_type
      make_DIRECTORY (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIRECTORY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENTS (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENTS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENTS (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENTS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USER_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_USER_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_USER_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_USER_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PASSWORD_FILE (location_type l)
      {
        return symbol_type (token::TOKEN_PASSWORD_FILE, std::move (l));
      }
#else
      static
      symbol_type
      make_PASSWORD_FILE (const location_type& l)
      {
        return symbol_type (token::TOKEN_PASSWORD_FILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CERT_REQUIRED (location_type l)
      {
        return symbol_type (token::TOKEN_CERT_REQUIRED, std::move (l));
      }
#else
      static
      symbol_type
      make_CERT_REQUIRED (const location_type& l)
      {
        return symbol_type (token::TOKEN_CERT_REQUIRED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HTTP_HEADERS (location_type l)
      {
        return symbol_type (token::TOKEN_HTTP_HEADERS, std::move (l));
      }
#else
      static
      symbol_type
      make_HTTP_HEADERS (const location_type& l)
      {
        return symbol_type (token::TOKEN_HTTP_HEADERS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VALUE (location_type l)
      {
        return symbol_type (token::TOKEN_VALUE, std::move (l));
      }
#else
      static
      symbol_type
      make_VALUE (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUE, l);
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
      yylast_ = 1649,     ///< Last index in yytable_.
      yynnts_ = 492,  ///< Number of nonterminal symbols.
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
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234
    };
    // Last valid token kind.
    const int code_max = 489;

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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_duid_type: // duid_type
      case symbol_kind::S_control_socket_type_value: // control_socket_type_value
      case symbol_kind::S_auth_type_value: // auth_type_value
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
#line 5986 "dhcp6_parser.h"




#endif // !YY_PARSER6_DHCP6_PARSER_H_INCLUDED
