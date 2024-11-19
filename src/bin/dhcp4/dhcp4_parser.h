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
 ** \file dhcp4_parser.h
 ** Define the isc::dhcp::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_PARSER4_DHCP4_PARSER_H_INCLUDED
# define YY_PARSER4_DHCP4_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 17 "dhcp4_parser.yy"

#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp4/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;

#line 61 "dhcp4_parser.h"

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
#ifndef PARSER4__ASSERT
# include <cassert>
# define PARSER4__ASSERT assert
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
#ifndef PARSER4_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PARSER4_DEBUG 1
#  else
#   define PARSER4_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PARSER4_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PARSER4_DEBUG */

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 210 "dhcp4_parser.h"




  /// A Bison parser.
  class Dhcp4Parser
  {
  public:
#ifdef PARSER4_STYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define PARSER4_STYPE in C++, use %define api.value.type"
# endif
    typedef PARSER4_STYPE value_type;
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
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      PARSER4__ASSERT (!yytypeid_);
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == typeid (T));
      PARSER4__ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == typeid (T));
      PARSER4__ASSERT (sizeof (T) <= size);
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
      PARSER4__ASSERT (yytypeid_);
      PARSER4__ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // socket_type
      // outbound_interface_value
      // on_fail_mode
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
        TOKEN_PARSER4_EMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_PARSER4_error = 256,     // error
    TOKEN_PARSER4_UNDEF = 257,     // "invalid token"
    TOKEN_COMMA = 258,             // ","
    TOKEN_COLON = 259,             // ":"
    TOKEN_LSQUARE_BRACKET = 260,   // "["
    TOKEN_RSQUARE_BRACKET = 261,   // "]"
    TOKEN_LCURLY_BRACKET = 262,    // "{"
    TOKEN_RCURLY_BRACKET = 263,    // "}"
    TOKEN_NULL_TYPE = 264,         // "null"
    TOKEN_DHCP4 = 265,             // "Dhcp4"
    TOKEN_CONFIG_CONTROL = 266,    // "config-control"
    TOKEN_CONFIG_DATABASES = 267,  // "config-databases"
    TOKEN_CONFIG_FETCH_WAIT_TIME = 268, // "config-fetch-wait-time"
    TOKEN_INTERFACES_CONFIG = 269, // "interfaces-config"
    TOKEN_INTERFACES = 270,        // "interfaces"
    TOKEN_DHCP_SOCKET_TYPE = 271,  // "dhcp-socket-type"
    TOKEN_RAW = 272,               // "raw"
    TOKEN_UDP = 273,               // "udp"
    TOKEN_OUTBOUND_INTERFACE = 274, // "outbound-interface"
    TOKEN_SAME_AS_INBOUND = 275,   // "same-as-inbound"
    TOKEN_USE_ROUTING = 276,       // "use-routing"
    TOKEN_RE_DETECT = 277,         // "re-detect"
    TOKEN_SERVICE_SOCKETS_REQUIRE_ALL = 278, // "service-sockets-require-all"
    TOKEN_SERVICE_SOCKETS_RETRY_WAIT_TIME = 279, // "service-sockets-retry-wait-time"
    TOKEN_SERVICE_SOCKETS_MAX_RETRIES = 280, // "service-sockets-max-retries"
    TOKEN_SANITY_CHECKS = 281,     // "sanity-checks"
    TOKEN_LEASE_CHECKS = 282,      // "lease-checks"
    TOKEN_EXTENDED_INFO_CHECKS = 283, // "extended-info-checks"
    TOKEN_ECHO_CLIENT_ID = 284,    // "echo-client-id"
    TOKEN_MATCH_CLIENT_ID = 285,   // "match-client-id"
    TOKEN_AUTHORITATIVE = 286,     // "authoritative"
    TOKEN_NEXT_SERVER = 287,       // "next-server"
    TOKEN_SERVER_HOSTNAME = 288,   // "server-hostname"
    TOKEN_BOOT_FILE_NAME = 289,    // "boot-file-name"
    TOKEN_OFFER_LFT = 290,         // "offer-lifetime"
    TOKEN_STASH_AGENT_OPTIONS = 291, // "stash-agent-options"
    TOKEN_LEASE_DATABASE = 292,    // "lease-database"
    TOKEN_HOSTS_DATABASE = 293,    // "hosts-database"
    TOKEN_HOSTS_DATABASES = 294,   // "hosts-databases"
    TOKEN_TYPE = 295,              // "type"
    TOKEN_USER = 296,              // "user"
    TOKEN_PASSWORD = 297,          // "password"
    TOKEN_HOST = 298,              // "host"
    TOKEN_PORT = 299,              // "port"
    TOKEN_PERSIST = 300,           // "persist"
    TOKEN_LFC_INTERVAL = 301,      // "lfc-interval"
    TOKEN_READONLY = 302,          // "readonly"
    TOKEN_CONNECT_TIMEOUT = 303,   // "connect-timeout"
    TOKEN_READ_TIMEOUT = 304,      // "read-timeout"
    TOKEN_WRITE_TIMEOUT = 305,     // "write-timeout"
    TOKEN_TCP_USER_TIMEOUT = 306,  // "tcp-user-timeout"
    TOKEN_MAX_RECONNECT_TRIES = 307, // "max-reconnect-tries"
    TOKEN_RECONNECT_WAIT_TIME = 308, // "reconnect-wait-time"
    TOKEN_ON_FAIL = 309,           // "on-fail"
    TOKEN_STOP_RETRY_EXIT = 310,   // "stop-retry-exit"
    TOKEN_SERVE_RETRY_EXIT = 311,  // "serve-retry-exit"
    TOKEN_SERVE_RETRY_CONTINUE = 312, // "serve-retry-continue"
    TOKEN_RETRY_ON_STARTUP = 313,  // "retry-on-startup"
    TOKEN_MAX_ROW_ERRORS = 314,    // "max-row-errors"
    TOKEN_TRUST_ANCHOR = 315,      // "trust-anchor"
    TOKEN_CERT_FILE = 316,         // "cert-file"
    TOKEN_KEY_FILE = 317,          // "key-file"
    TOKEN_CIPHER_LIST = 318,       // "cipher-list"
    TOKEN_VALID_LIFETIME = 319,    // "valid-lifetime"
    TOKEN_MIN_VALID_LIFETIME = 320, // "min-valid-lifetime"
    TOKEN_MAX_VALID_LIFETIME = 321, // "max-valid-lifetime"
    TOKEN_RENEW_TIMER = 322,       // "renew-timer"
    TOKEN_REBIND_TIMER = 323,      // "rebind-timer"
    TOKEN_CALCULATE_TEE_TIMES = 324, // "calculate-tee-times"
    TOKEN_T1_PERCENT = 325,        // "t1-percent"
    TOKEN_T2_PERCENT = 326,        // "t2-percent"
    TOKEN_CACHE_THRESHOLD = 327,   // "cache-threshold"
    TOKEN_CACHE_MAX_AGE = 328,     // "cache-max-age"
    TOKEN_DECLINE_PROBATION_PERIOD = 329, // "decline-probation-period"
    TOKEN_SERVER_TAG = 330,        // "server-tag"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_COUNT = 331, // "statistic-default-sample-count"
    TOKEN_STATISTIC_DEFAULT_SAMPLE_AGE = 332, // "statistic-default-sample-age"
    TOKEN_DDNS_SEND_UPDATES = 333, // "ddns-send-updates"
    TOKEN_DDNS_OVERRIDE_NO_UPDATE = 334, // "ddns-override-no-update"
    TOKEN_DDNS_OVERRIDE_CLIENT_UPDATE = 335, // "ddns-override-client-update"
    TOKEN_DDNS_REPLACE_CLIENT_NAME = 336, // "ddns-replace-client-name"
    TOKEN_DDNS_GENERATED_PREFIX = 337, // "ddns-generated-prefix"
    TOKEN_DDNS_QUALIFYING_SUFFIX = 338, // "ddns-qualifying-suffix"
    TOKEN_DDNS_UPDATE_ON_RENEW = 339, // "ddns-update-on-renew"
    TOKEN_DDNS_USE_CONFLICT_RESOLUTION = 340, // "ddns-use-conflict-resolution"
    TOKEN_DDNS_TTL_PERCENT = 341,  // "ddns-ttl-percent"
    TOKEN_DDNS_TTL = 342,          // "ddns-ttl"
    TOKEN_DDNS_TTL_MIN = 343,      // "ddns-ttl-min"
    TOKEN_DDNS_TTL_MAX = 344,      // "ddns-ttl-mix"
    TOKEN_STORE_EXTENDED_INFO = 345, // "store-extended-info"
    TOKEN_SUBNET4 = 346,           // "subnet4"
    TOKEN_SUBNET_4O6_INTERFACE = 347, // "4o6-interface"
    TOKEN_SUBNET_4O6_INTERFACE_ID = 348, // "4o6-interface-id"
    TOKEN_SUBNET_4O6_SUBNET = 349, // "4o6-subnet"
    TOKEN_OPTION_DEF = 350,        // "option-def"
    TOKEN_OPTION_DATA = 351,       // "option-data"
    TOKEN_NAME = 352,              // "name"
    TOKEN_DATA = 353,              // "data"
    TOKEN_CODE = 354,              // "code"
    TOKEN_SPACE = 355,             // "space"
    TOKEN_CSV_FORMAT = 356,        // "csv-format"
    TOKEN_ALWAYS_SEND = 357,       // "always-send"
    TOKEN_NEVER_SEND = 358,        // "never-send"
    TOKEN_RECORD_TYPES = 359,      // "record-types"
    TOKEN_ENCAPSULATE = 360,       // "encapsulate"
    TOKEN_ARRAY = 361,             // "array"
    TOKEN_PARKED_PACKET_LIMIT = 362, // "parked-packet-limit"
    TOKEN_ALLOCATOR = 363,         // "allocator"
    TOKEN_DDNS_CONFLICT_RESOLUTION_MODE = 364, // "ddns-conflict-resolution-mode"
    TOKEN_CHECK_WITH_DHCID = 365,  // "check-with-dhcid"
    TOKEN_NO_CHECK_WITH_DHCID = 366, // "no-check-with-dhcid"
    TOKEN_CHECK_EXISTS_WITH_DHCID = 367, // "check-exists-with-dhcid"
    TOKEN_NO_CHECK_WITHOUT_DHCID = 368, // "no-check-without-dhcid"
    TOKEN_SHARED_NETWORKS = 369,   // "shared-networks"
    TOKEN_POOLS = 370,             // "pools"
    TOKEN_POOL = 371,              // "pool"
    TOKEN_USER_CONTEXT = 372,      // "user-context"
    TOKEN_COMMENT = 373,           // "comment"
    TOKEN_SUBNET = 374,            // "subnet"
    TOKEN_INTERFACE = 375,         // "interface"
    TOKEN_ID = 376,                // "id"
    TOKEN_RESERVATIONS_GLOBAL = 377, // "reservations-global"
    TOKEN_RESERVATIONS_IN_SUBNET = 378, // "reservations-in-subnet"
    TOKEN_RESERVATIONS_OUT_OF_POOL = 379, // "reservations-out-of-pool"
    TOKEN_HOST_RESERVATION_IDENTIFIERS = 380, // "host-reservation-identifiers"
    TOKEN_CLIENT_CLASSES = 381,    // "client-classes"
    TOKEN_REQUIRE_CLIENT_CLASSES = 382, // "require-client-classes"
    TOKEN_EVALUATE_ADDITIONAL_CLASSES = 383, // "evaluate-additional-classes"
    TOKEN_TEST = 384,              // "test"
    TOKEN_TEMPLATE_TEST = 385,     // "template-test"
    TOKEN_ONLY_IF_REQUIRED = 386,  // "only-if-required"
    TOKEN_ONLY_IN_ADDITIONAL_LIST = 387, // "only-in-additional-list"
    TOKEN_CLIENT_CLASS = 388,      // "client-class"
    TOKEN_POOL_ID = 389,           // "pool-id"
    TOKEN_RESERVATIONS = 390,      // "reservations"
    TOKEN_IP_ADDRESS = 391,        // "ip-address"
    TOKEN_DUID = 392,              // "duid"
    TOKEN_HW_ADDRESS = 393,        // "hw-address"
    TOKEN_CIRCUIT_ID = 394,        // "circuit-id"
    TOKEN_CLIENT_ID = 395,         // "client-id"
    TOKEN_HOSTNAME = 396,          // "hostname"
    TOKEN_FLEX_ID = 397,           // "flex-id"
    TOKEN_RELAY = 398,             // "relay"
    TOKEN_IP_ADDRESSES = 399,      // "ip-addresses"
    TOKEN_HOOKS_LIBRARIES = 400,   // "hooks-libraries"
    TOKEN_LIBRARY = 401,           // "library"
    TOKEN_PARAMETERS = 402,        // "parameters"
    TOKEN_EXPIRED_LEASES_PROCESSING = 403, // "expired-leases-processing"
    TOKEN_RECLAIM_TIMER_WAIT_TIME = 404, // "reclaim-timer-wait-time"
    TOKEN_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 405, // "flush-reclaimed-timer-wait-time"
    TOKEN_HOLD_RECLAIMED_TIME = 406, // "hold-reclaimed-time"
    TOKEN_MAX_RECLAIM_LEASES = 407, // "max-reclaim-leases"
    TOKEN_MAX_RECLAIM_TIME = 408,  // "max-reclaim-time"
    TOKEN_UNWARNED_RECLAIM_CYCLES = 409, // "unwarned-reclaim-cycles"
    TOKEN_DHCP4O6_PORT = 410,      // "dhcp4o6-port"
    TOKEN_DHCP_MULTI_THREADING = 411, // "multi-threading"
    TOKEN_ENABLE_MULTI_THREADING = 412, // "enable-multi-threading"
    TOKEN_THREAD_POOL_SIZE = 413,  // "thread-pool-size"
    TOKEN_PACKET_QUEUE_SIZE = 414, // "packet-queue-size"
    TOKEN_CONTROL_SOCKET = 415,    // "control-socket"
    TOKEN_CONTROL_SOCKETS = 416,   // "control-sockets"
    TOKEN_SOCKET_TYPE = 417,       // "socket-type"
    TOKEN_UNIX = 418,              // "unix"
    TOKEN_HTTP = 419,              // "http"
    TOKEN_HTTPS = 420,             // "https"
    TOKEN_SOCKET_NAME = 421,       // "socket-name"
    TOKEN_SOCKET_ADDRESS = 422,    // "socket-address"
    TOKEN_SOCKET_PORT = 423,       // "socket-port"
    TOKEN_AUTHENTICATION = 424,    // "authentication"
    TOKEN_BASIC = 425,             // "basic"
    TOKEN_REALM = 426,             // "realm"
    TOKEN_DIRECTORY = 427,         // "directory"
    TOKEN_CLIENTS = 428,           // "clients"
    TOKEN_USER_FILE = 429,         // "user-file"
    TOKEN_PASSWORD_FILE = 430,     // "password-file"
    TOKEN_CERT_REQUIRED = 431,     // "cert-required"
    TOKEN_HTTP_HEADERS = 432,      // "http-headers"
    TOKEN_VALUE = 433,             // "value"
    TOKEN_DHCP_QUEUE_CONTROL = 434, // "dhcp-queue-control"
    TOKEN_ENABLE_QUEUE = 435,      // "enable-queue"
    TOKEN_QUEUE_TYPE = 436,        // "queue-type"
    TOKEN_CAPACITY = 437,          // "capacity"
    TOKEN_DHCP_DDNS = 438,         // "dhcp-ddns"
    TOKEN_ENABLE_UPDATES = 439,    // "enable-updates"
    TOKEN_SERVER_IP = 440,         // "server-ip"
    TOKEN_SERVER_PORT = 441,       // "server-port"
    TOKEN_SENDER_IP = 442,         // "sender-ip"
    TOKEN_SENDER_PORT = 443,       // "sender-port"
    TOKEN_MAX_QUEUE_SIZE = 444,    // "max-queue-size"
    TOKEN_NCR_PROTOCOL = 445,      // "ncr-protocol"
    TOKEN_NCR_FORMAT = 446,        // "ncr-format"
    TOKEN_TCP = 447,               // "tcp"
    TOKEN_JSON = 448,              // "JSON"
    TOKEN_WHEN_PRESENT = 449,      // "when-present"
    TOKEN_NEVER = 450,             // "never"
    TOKEN_ALWAYS = 451,            // "always"
    TOKEN_WHEN_NOT_PRESENT = 452,  // "when-not-present"
    TOKEN_HOSTNAME_CHAR_SET = 453, // "hostname-char-set"
    TOKEN_HOSTNAME_CHAR_REPLACEMENT = 454, // "hostname-char-replacement"
    TOKEN_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 455, // "early-global-reservations-lookup"
    TOKEN_IP_RESERVATIONS_UNIQUE = 456, // "ip-reservations-unique"
    TOKEN_RESERVATIONS_LOOKUP_FIRST = 457, // "reservations-lookup-first"
    TOKEN_LOGGERS = 458,           // "loggers"
    TOKEN_OUTPUT_OPTIONS = 459,    // "output-options"
    TOKEN_OUTPUT = 460,            // "output"
    TOKEN_DEBUGLEVEL = 461,        // "debuglevel"
    TOKEN_SEVERITY = 462,          // "severity"
    TOKEN_FLUSH = 463,             // "flush"
    TOKEN_MAXSIZE = 464,           // "maxsize"
    TOKEN_MAXVER = 465,            // "maxver"
    TOKEN_PATTERN = 466,           // "pattern"
    TOKEN_COMPATIBILITY = 467,     // "compatibility"
    TOKEN_LENIENT_OPTION_PARSING = 468, // "lenient-option-parsing"
    TOKEN_IGNORE_DHCP_SERVER_ID = 469, // "ignore-dhcp-server-identifier"
    TOKEN_IGNORE_RAI_LINK_SEL = 470, // "ignore-rai-link-selection"
    TOKEN_EXCLUDE_FIRST_LAST_24 = 471, // "exclude-first-last-24"
    TOKEN_TOPLEVEL_JSON = 472,     // TOPLEVEL_JSON
    TOKEN_TOPLEVEL_DHCP4 = 473,    // TOPLEVEL_DHCP4
    TOKEN_SUB_DHCP4 = 474,         // SUB_DHCP4
    TOKEN_SUB_INTERFACES4 = 475,   // SUB_INTERFACES4
    TOKEN_SUB_SUBNET4 = 476,       // SUB_SUBNET4
    TOKEN_SUB_POOL4 = 477,         // SUB_POOL4
    TOKEN_SUB_RESERVATION = 478,   // SUB_RESERVATION
    TOKEN_SUB_OPTION_DEFS = 479,   // SUB_OPTION_DEFS
    TOKEN_SUB_OPTION_DEF = 480,    // SUB_OPTION_DEF
    TOKEN_SUB_OPTION_DATA = 481,   // SUB_OPTION_DATA
    TOKEN_SUB_HOOKS_LIBRARY = 482, // SUB_HOOKS_LIBRARY
    TOKEN_SUB_DHCP_DDNS = 483,     // SUB_DHCP_DDNS
    TOKEN_SUB_CONFIG_CONTROL = 484, // SUB_CONFIG_CONTROL
    TOKEN_STRING = 485,            // "constant string"
    TOKEN_INTEGER = 486,           // "integer"
    TOKEN_FLOAT = 487,             // "floating point"
    TOKEN_BOOLEAN = 488            // "boolean"
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
        YYNTOKENS = 234, ///< Number of tokens.
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
        S_DHCP4 = 10,                            // "Dhcp4"
        S_CONFIG_CONTROL = 11,                   // "config-control"
        S_CONFIG_DATABASES = 12,                 // "config-databases"
        S_CONFIG_FETCH_WAIT_TIME = 13,           // "config-fetch-wait-time"
        S_INTERFACES_CONFIG = 14,                // "interfaces-config"
        S_INTERFACES = 15,                       // "interfaces"
        S_DHCP_SOCKET_TYPE = 16,                 // "dhcp-socket-type"
        S_RAW = 17,                              // "raw"
        S_UDP = 18,                              // "udp"
        S_OUTBOUND_INTERFACE = 19,               // "outbound-interface"
        S_SAME_AS_INBOUND = 20,                  // "same-as-inbound"
        S_USE_ROUTING = 21,                      // "use-routing"
        S_RE_DETECT = 22,                        // "re-detect"
        S_SERVICE_SOCKETS_REQUIRE_ALL = 23,      // "service-sockets-require-all"
        S_SERVICE_SOCKETS_RETRY_WAIT_TIME = 24,  // "service-sockets-retry-wait-time"
        S_SERVICE_SOCKETS_MAX_RETRIES = 25,      // "service-sockets-max-retries"
        S_SANITY_CHECKS = 26,                    // "sanity-checks"
        S_LEASE_CHECKS = 27,                     // "lease-checks"
        S_EXTENDED_INFO_CHECKS = 28,             // "extended-info-checks"
        S_ECHO_CLIENT_ID = 29,                   // "echo-client-id"
        S_MATCH_CLIENT_ID = 30,                  // "match-client-id"
        S_AUTHORITATIVE = 31,                    // "authoritative"
        S_NEXT_SERVER = 32,                      // "next-server"
        S_SERVER_HOSTNAME = 33,                  // "server-hostname"
        S_BOOT_FILE_NAME = 34,                   // "boot-file-name"
        S_OFFER_LFT = 35,                        // "offer-lifetime"
        S_STASH_AGENT_OPTIONS = 36,              // "stash-agent-options"
        S_LEASE_DATABASE = 37,                   // "lease-database"
        S_HOSTS_DATABASE = 38,                   // "hosts-database"
        S_HOSTS_DATABASES = 39,                  // "hosts-databases"
        S_TYPE = 40,                             // "type"
        S_USER = 41,                             // "user"
        S_PASSWORD = 42,                         // "password"
        S_HOST = 43,                             // "host"
        S_PORT = 44,                             // "port"
        S_PERSIST = 45,                          // "persist"
        S_LFC_INTERVAL = 46,                     // "lfc-interval"
        S_READONLY = 47,                         // "readonly"
        S_CONNECT_TIMEOUT = 48,                  // "connect-timeout"
        S_READ_TIMEOUT = 49,                     // "read-timeout"
        S_WRITE_TIMEOUT = 50,                    // "write-timeout"
        S_TCP_USER_TIMEOUT = 51,                 // "tcp-user-timeout"
        S_MAX_RECONNECT_TRIES = 52,              // "max-reconnect-tries"
        S_RECONNECT_WAIT_TIME = 53,              // "reconnect-wait-time"
        S_ON_FAIL = 54,                          // "on-fail"
        S_STOP_RETRY_EXIT = 55,                  // "stop-retry-exit"
        S_SERVE_RETRY_EXIT = 56,                 // "serve-retry-exit"
        S_SERVE_RETRY_CONTINUE = 57,             // "serve-retry-continue"
        S_RETRY_ON_STARTUP = 58,                 // "retry-on-startup"
        S_MAX_ROW_ERRORS = 59,                   // "max-row-errors"
        S_TRUST_ANCHOR = 60,                     // "trust-anchor"
        S_CERT_FILE = 61,                        // "cert-file"
        S_KEY_FILE = 62,                         // "key-file"
        S_CIPHER_LIST = 63,                      // "cipher-list"
        S_VALID_LIFETIME = 64,                   // "valid-lifetime"
        S_MIN_VALID_LIFETIME = 65,               // "min-valid-lifetime"
        S_MAX_VALID_LIFETIME = 66,               // "max-valid-lifetime"
        S_RENEW_TIMER = 67,                      // "renew-timer"
        S_REBIND_TIMER = 68,                     // "rebind-timer"
        S_CALCULATE_TEE_TIMES = 69,              // "calculate-tee-times"
        S_T1_PERCENT = 70,                       // "t1-percent"
        S_T2_PERCENT = 71,                       // "t2-percent"
        S_CACHE_THRESHOLD = 72,                  // "cache-threshold"
        S_CACHE_MAX_AGE = 73,                    // "cache-max-age"
        S_DECLINE_PROBATION_PERIOD = 74,         // "decline-probation-period"
        S_SERVER_TAG = 75,                       // "server-tag"
        S_STATISTIC_DEFAULT_SAMPLE_COUNT = 76,   // "statistic-default-sample-count"
        S_STATISTIC_DEFAULT_SAMPLE_AGE = 77,     // "statistic-default-sample-age"
        S_DDNS_SEND_UPDATES = 78,                // "ddns-send-updates"
        S_DDNS_OVERRIDE_NO_UPDATE = 79,          // "ddns-override-no-update"
        S_DDNS_OVERRIDE_CLIENT_UPDATE = 80,      // "ddns-override-client-update"
        S_DDNS_REPLACE_CLIENT_NAME = 81,         // "ddns-replace-client-name"
        S_DDNS_GENERATED_PREFIX = 82,            // "ddns-generated-prefix"
        S_DDNS_QUALIFYING_SUFFIX = 83,           // "ddns-qualifying-suffix"
        S_DDNS_UPDATE_ON_RENEW = 84,             // "ddns-update-on-renew"
        S_DDNS_USE_CONFLICT_RESOLUTION = 85,     // "ddns-use-conflict-resolution"
        S_DDNS_TTL_PERCENT = 86,                 // "ddns-ttl-percent"
        S_DDNS_TTL = 87,                         // "ddns-ttl"
        S_DDNS_TTL_MIN = 88,                     // "ddns-ttl-min"
        S_DDNS_TTL_MAX = 89,                     // "ddns-ttl-mix"
        S_STORE_EXTENDED_INFO = 90,              // "store-extended-info"
        S_SUBNET4 = 91,                          // "subnet4"
        S_SUBNET_4O6_INTERFACE = 92,             // "4o6-interface"
        S_SUBNET_4O6_INTERFACE_ID = 93,          // "4o6-interface-id"
        S_SUBNET_4O6_SUBNET = 94,                // "4o6-subnet"
        S_OPTION_DEF = 95,                       // "option-def"
        S_OPTION_DATA = 96,                      // "option-data"
        S_NAME = 97,                             // "name"
        S_DATA = 98,                             // "data"
        S_CODE = 99,                             // "code"
        S_SPACE = 100,                           // "space"
        S_CSV_FORMAT = 101,                      // "csv-format"
        S_ALWAYS_SEND = 102,                     // "always-send"
        S_NEVER_SEND = 103,                      // "never-send"
        S_RECORD_TYPES = 104,                    // "record-types"
        S_ENCAPSULATE = 105,                     // "encapsulate"
        S_ARRAY = 106,                           // "array"
        S_PARKED_PACKET_LIMIT = 107,             // "parked-packet-limit"
        S_ALLOCATOR = 108,                       // "allocator"
        S_DDNS_CONFLICT_RESOLUTION_MODE = 109,   // "ddns-conflict-resolution-mode"
        S_CHECK_WITH_DHCID = 110,                // "check-with-dhcid"
        S_NO_CHECK_WITH_DHCID = 111,             // "no-check-with-dhcid"
        S_CHECK_EXISTS_WITH_DHCID = 112,         // "check-exists-with-dhcid"
        S_NO_CHECK_WITHOUT_DHCID = 113,          // "no-check-without-dhcid"
        S_SHARED_NETWORKS = 114,                 // "shared-networks"
        S_POOLS = 115,                           // "pools"
        S_POOL = 116,                            // "pool"
        S_USER_CONTEXT = 117,                    // "user-context"
        S_COMMENT = 118,                         // "comment"
        S_SUBNET = 119,                          // "subnet"
        S_INTERFACE = 120,                       // "interface"
        S_ID = 121,                              // "id"
        S_RESERVATIONS_GLOBAL = 122,             // "reservations-global"
        S_RESERVATIONS_IN_SUBNET = 123,          // "reservations-in-subnet"
        S_RESERVATIONS_OUT_OF_POOL = 124,        // "reservations-out-of-pool"
        S_HOST_RESERVATION_IDENTIFIERS = 125,    // "host-reservation-identifiers"
        S_CLIENT_CLASSES = 126,                  // "client-classes"
        S_REQUIRE_CLIENT_CLASSES = 127,          // "require-client-classes"
        S_EVALUATE_ADDITIONAL_CLASSES = 128,     // "evaluate-additional-classes"
        S_TEST = 129,                            // "test"
        S_TEMPLATE_TEST = 130,                   // "template-test"
        S_ONLY_IF_REQUIRED = 131,                // "only-if-required"
        S_ONLY_IN_ADDITIONAL_LIST = 132,         // "only-in-additional-list"
        S_CLIENT_CLASS = 133,                    // "client-class"
        S_POOL_ID = 134,                         // "pool-id"
        S_RESERVATIONS = 135,                    // "reservations"
        S_IP_ADDRESS = 136,                      // "ip-address"
        S_DUID = 137,                            // "duid"
        S_HW_ADDRESS = 138,                      // "hw-address"
        S_CIRCUIT_ID = 139,                      // "circuit-id"
        S_CLIENT_ID = 140,                       // "client-id"
        S_HOSTNAME = 141,                        // "hostname"
        S_FLEX_ID = 142,                         // "flex-id"
        S_RELAY = 143,                           // "relay"
        S_IP_ADDRESSES = 144,                    // "ip-addresses"
        S_HOOKS_LIBRARIES = 145,                 // "hooks-libraries"
        S_LIBRARY = 146,                         // "library"
        S_PARAMETERS = 147,                      // "parameters"
        S_EXPIRED_LEASES_PROCESSING = 148,       // "expired-leases-processing"
        S_RECLAIM_TIMER_WAIT_TIME = 149,         // "reclaim-timer-wait-time"
        S_FLUSH_RECLAIMED_TIMER_WAIT_TIME = 150, // "flush-reclaimed-timer-wait-time"
        S_HOLD_RECLAIMED_TIME = 151,             // "hold-reclaimed-time"
        S_MAX_RECLAIM_LEASES = 152,              // "max-reclaim-leases"
        S_MAX_RECLAIM_TIME = 153,                // "max-reclaim-time"
        S_UNWARNED_RECLAIM_CYCLES = 154,         // "unwarned-reclaim-cycles"
        S_DHCP4O6_PORT = 155,                    // "dhcp4o6-port"
        S_DHCP_MULTI_THREADING = 156,            // "multi-threading"
        S_ENABLE_MULTI_THREADING = 157,          // "enable-multi-threading"
        S_THREAD_POOL_SIZE = 158,                // "thread-pool-size"
        S_PACKET_QUEUE_SIZE = 159,               // "packet-queue-size"
        S_CONTROL_SOCKET = 160,                  // "control-socket"
        S_CONTROL_SOCKETS = 161,                 // "control-sockets"
        S_SOCKET_TYPE = 162,                     // "socket-type"
        S_UNIX = 163,                            // "unix"
        S_HTTP = 164,                            // "http"
        S_HTTPS = 165,                           // "https"
        S_SOCKET_NAME = 166,                     // "socket-name"
        S_SOCKET_ADDRESS = 167,                  // "socket-address"
        S_SOCKET_PORT = 168,                     // "socket-port"
        S_AUTHENTICATION = 169,                  // "authentication"
        S_BASIC = 170,                           // "basic"
        S_REALM = 171,                           // "realm"
        S_DIRECTORY = 172,                       // "directory"
        S_CLIENTS = 173,                         // "clients"
        S_USER_FILE = 174,                       // "user-file"
        S_PASSWORD_FILE = 175,                   // "password-file"
        S_CERT_REQUIRED = 176,                   // "cert-required"
        S_HTTP_HEADERS = 177,                    // "http-headers"
        S_VALUE = 178,                           // "value"
        S_DHCP_QUEUE_CONTROL = 179,              // "dhcp-queue-control"
        S_ENABLE_QUEUE = 180,                    // "enable-queue"
        S_QUEUE_TYPE = 181,                      // "queue-type"
        S_CAPACITY = 182,                        // "capacity"
        S_DHCP_DDNS = 183,                       // "dhcp-ddns"
        S_ENABLE_UPDATES = 184,                  // "enable-updates"
        S_SERVER_IP = 185,                       // "server-ip"
        S_SERVER_PORT = 186,                     // "server-port"
        S_SENDER_IP = 187,                       // "sender-ip"
        S_SENDER_PORT = 188,                     // "sender-port"
        S_MAX_QUEUE_SIZE = 189,                  // "max-queue-size"
        S_NCR_PROTOCOL = 190,                    // "ncr-protocol"
        S_NCR_FORMAT = 191,                      // "ncr-format"
        S_TCP = 192,                             // "tcp"
        S_JSON = 193,                            // "JSON"
        S_WHEN_PRESENT = 194,                    // "when-present"
        S_NEVER = 195,                           // "never"
        S_ALWAYS = 196,                          // "always"
        S_WHEN_NOT_PRESENT = 197,                // "when-not-present"
        S_HOSTNAME_CHAR_SET = 198,               // "hostname-char-set"
        S_HOSTNAME_CHAR_REPLACEMENT = 199,       // "hostname-char-replacement"
        S_EARLY_GLOBAL_RESERVATIONS_LOOKUP = 200, // "early-global-reservations-lookup"
        S_IP_RESERVATIONS_UNIQUE = 201,          // "ip-reservations-unique"
        S_RESERVATIONS_LOOKUP_FIRST = 202,       // "reservations-lookup-first"
        S_LOGGERS = 203,                         // "loggers"
        S_OUTPUT_OPTIONS = 204,                  // "output-options"
        S_OUTPUT = 205,                          // "output"
        S_DEBUGLEVEL = 206,                      // "debuglevel"
        S_SEVERITY = 207,                        // "severity"
        S_FLUSH = 208,                           // "flush"
        S_MAXSIZE = 209,                         // "maxsize"
        S_MAXVER = 210,                          // "maxver"
        S_PATTERN = 211,                         // "pattern"
        S_COMPATIBILITY = 212,                   // "compatibility"
        S_LENIENT_OPTION_PARSING = 213,          // "lenient-option-parsing"
        S_IGNORE_DHCP_SERVER_ID = 214,           // "ignore-dhcp-server-identifier"
        S_IGNORE_RAI_LINK_SEL = 215,             // "ignore-rai-link-selection"
        S_EXCLUDE_FIRST_LAST_24 = 216,           // "exclude-first-last-24"
        S_TOPLEVEL_JSON = 217,                   // TOPLEVEL_JSON
        S_TOPLEVEL_DHCP4 = 218,                  // TOPLEVEL_DHCP4
        S_SUB_DHCP4 = 219,                       // SUB_DHCP4
        S_SUB_INTERFACES4 = 220,                 // SUB_INTERFACES4
        S_SUB_SUBNET4 = 221,                     // SUB_SUBNET4
        S_SUB_POOL4 = 222,                       // SUB_POOL4
        S_SUB_RESERVATION = 223,                 // SUB_RESERVATION
        S_SUB_OPTION_DEFS = 224,                 // SUB_OPTION_DEFS
        S_SUB_OPTION_DEF = 225,                  // SUB_OPTION_DEF
        S_SUB_OPTION_DATA = 226,                 // SUB_OPTION_DATA
        S_SUB_HOOKS_LIBRARY = 227,               // SUB_HOOKS_LIBRARY
        S_SUB_DHCP_DDNS = 228,                   // SUB_DHCP_DDNS
        S_SUB_CONFIG_CONTROL = 229,              // SUB_CONFIG_CONTROL
        S_STRING = 230,                          // "constant string"
        S_INTEGER = 231,                         // "integer"
        S_FLOAT = 232,                           // "floating point"
        S_BOOLEAN = 233,                         // "boolean"
        S_YYACCEPT = 234,                        // $accept
        S_start = 235,                           // start
        S_236_1 = 236,                           // $@1
        S_237_2 = 237,                           // $@2
        S_238_3 = 238,                           // $@3
        S_239_4 = 239,                           // $@4
        S_240_5 = 240,                           // $@5
        S_241_6 = 241,                           // $@6
        S_242_7 = 242,                           // $@7
        S_243_8 = 243,                           // $@8
        S_244_9 = 244,                           // $@9
        S_245_10 = 245,                          // $@10
        S_246_11 = 246,                          // $@11
        S_247_12 = 247,                          // $@12
        S_248_13 = 248,                          // $@13
        S_value = 249,                           // value
        S_sub_json = 250,                        // sub_json
        S_map2 = 251,                            // map2
        S_252_14 = 252,                          // $@14
        S_map_value = 253,                       // map_value
        S_map_content = 254,                     // map_content
        S_not_empty_map = 255,                   // not_empty_map
        S_list_generic = 256,                    // list_generic
        S_257_15 = 257,                          // $@15
        S_list_content = 258,                    // list_content
        S_not_empty_list = 259,                  // not_empty_list
        S_list_strings = 260,                    // list_strings
        S_261_16 = 261,                          // $@16
        S_list_strings_content = 262,            // list_strings_content
        S_not_empty_list_strings = 263,          // not_empty_list_strings
        S_unknown_map_entry = 264,               // unknown_map_entry
        S_syntax_map = 265,                      // syntax_map
        S_266_17 = 266,                          // $@17
        S_global_object = 267,                   // global_object
        S_268_18 = 268,                          // $@18
        S_global_object_comma = 269,             // global_object_comma
        S_sub_dhcp4 = 270,                       // sub_dhcp4
        S_271_19 = 271,                          // $@19
        S_global_params = 272,                   // global_params
        S_global_param = 273,                    // global_param
        S_valid_lifetime = 274,                  // valid_lifetime
        S_min_valid_lifetime = 275,              // min_valid_lifetime
        S_max_valid_lifetime = 276,              // max_valid_lifetime
        S_renew_timer = 277,                     // renew_timer
        S_rebind_timer = 278,                    // rebind_timer
        S_calculate_tee_times = 279,             // calculate_tee_times
        S_t1_percent = 280,                      // t1_percent
        S_t2_percent = 281,                      // t2_percent
        S_cache_threshold = 282,                 // cache_threshold
        S_cache_max_age = 283,                   // cache_max_age
        S_decline_probation_period = 284,        // decline_probation_period
        S_server_tag = 285,                      // server_tag
        S_286_20 = 286,                          // $@20
        S_parked_packet_limit = 287,             // parked_packet_limit
        S_allocator = 288,                       // allocator
        S_289_21 = 289,                          // $@21
        S_echo_client_id = 290,                  // echo_client_id
        S_match_client_id = 291,                 // match_client_id
        S_authoritative = 292,                   // authoritative
        S_ddns_send_updates = 293,               // ddns_send_updates
        S_ddns_override_no_update = 294,         // ddns_override_no_update
        S_ddns_override_client_update = 295,     // ddns_override_client_update
        S_ddns_replace_client_name = 296,        // ddns_replace_client_name
        S_297_22 = 297,                          // $@22
        S_ddns_replace_client_name_value = 298,  // ddns_replace_client_name_value
        S_ddns_generated_prefix = 299,           // ddns_generated_prefix
        S_300_23 = 300,                          // $@23
        S_ddns_qualifying_suffix = 301,          // ddns_qualifying_suffix
        S_302_24 = 302,                          // $@24
        S_ddns_update_on_renew = 303,            // ddns_update_on_renew
        S_ddns_use_conflict_resolution = 304,    // ddns_use_conflict_resolution
        S_ddns_conflict_resolution_mode = 305,   // ddns_conflict_resolution_mode
        S_306_25 = 306,                          // $@25
        S_ddns_conflict_resolution_mode_value = 307, // ddns_conflict_resolution_mode_value
        S_ddns_ttl_percent = 308,                // ddns_ttl_percent
        S_ddns_ttl = 309,                        // ddns_ttl
        S_ddns_ttl_min = 310,                    // ddns_ttl_min
        S_ddns_ttl_max = 311,                    // ddns_ttl_max
        S_hostname_char_set = 312,               // hostname_char_set
        S_313_26 = 313,                          // $@26
        S_hostname_char_replacement = 314,       // hostname_char_replacement
        S_315_27 = 315,                          // $@27
        S_store_extended_info = 316,             // store_extended_info
        S_statistic_default_sample_count = 317,  // statistic_default_sample_count
        S_statistic_default_sample_age = 318,    // statistic_default_sample_age
        S_early_global_reservations_lookup = 319, // early_global_reservations_lookup
        S_ip_reservations_unique = 320,          // ip_reservations_unique
        S_reservations_lookup_first = 321,       // reservations_lookup_first
        S_offer_lifetime = 322,                  // offer_lifetime
        S_stash_agent_options = 323,             // stash_agent_options
        S_interfaces_config = 324,               // interfaces_config
        S_325_28 = 325,                          // $@28
        S_interfaces_config_params = 326,        // interfaces_config_params
        S_interfaces_config_param = 327,         // interfaces_config_param
        S_sub_interfaces4 = 328,                 // sub_interfaces4
        S_329_29 = 329,                          // $@29
        S_interfaces_list = 330,                 // interfaces_list
        S_331_30 = 331,                          // $@30
        S_dhcp_socket_type = 332,                // dhcp_socket_type
        S_333_31 = 333,                          // $@31
        S_socket_type = 334,                     // socket_type
        S_outbound_interface = 335,              // outbound_interface
        S_336_32 = 336,                          // $@32
        S_outbound_interface_value = 337,        // outbound_interface_value
        S_re_detect = 338,                       // re_detect
        S_service_sockets_require_all = 339,     // service_sockets_require_all
        S_service_sockets_retry_wait_time = 340, // service_sockets_retry_wait_time
        S_service_sockets_max_retries = 341,     // service_sockets_max_retries
        S_lease_database = 342,                  // lease_database
        S_343_33 = 343,                          // $@33
        S_sanity_checks = 344,                   // sanity_checks
        S_345_34 = 345,                          // $@34
        S_sanity_checks_params = 346,            // sanity_checks_params
        S_sanity_checks_param = 347,             // sanity_checks_param
        S_lease_checks = 348,                    // lease_checks
        S_349_35 = 349,                          // $@35
        S_extended_info_checks = 350,            // extended_info_checks
        S_351_36 = 351,                          // $@36
        S_hosts_database = 352,                  // hosts_database
        S_353_37 = 353,                          // $@37
        S_hosts_databases = 354,                 // hosts_databases
        S_355_38 = 355,                          // $@38
        S_database_list = 356,                   // database_list
        S_not_empty_database_list = 357,         // not_empty_database_list
        S_database = 358,                        // database
        S_359_39 = 359,                          // $@39
        S_database_map_params = 360,             // database_map_params
        S_database_map_param = 361,              // database_map_param
        S_database_type = 362,                   // database_type
        S_363_40 = 363,                          // $@40
        S_user = 364,                            // user
        S_365_41 = 365,                          // $@41
        S_password = 366,                        // password
        S_367_42 = 367,                          // $@42
        S_host = 368,                            // host
        S_369_43 = 369,                          // $@43
        S_port = 370,                            // port
        S_name = 371,                            // name
        S_372_44 = 372,                          // $@44
        S_persist = 373,                         // persist
        S_lfc_interval = 374,                    // lfc_interval
        S_readonly = 375,                        // readonly
        S_connect_timeout = 376,                 // connect_timeout
        S_read_timeout = 377,                    // read_timeout
        S_write_timeout = 378,                   // write_timeout
        S_tcp_user_timeout = 379,                // tcp_user_timeout
        S_max_reconnect_tries = 380,             // max_reconnect_tries
        S_reconnect_wait_time = 381,             // reconnect_wait_time
        S_on_fail = 382,                         // on_fail
        S_383_45 = 383,                          // $@45
        S_on_fail_mode = 384,                    // on_fail_mode
        S_retry_on_startup = 385,                // retry_on_startup
        S_max_row_errors = 386,                  // max_row_errors
        S_trust_anchor = 387,                    // trust_anchor
        S_388_46 = 388,                          // $@46
        S_cert_file = 389,                       // cert_file
        S_390_47 = 390,                          // $@47
        S_key_file = 391,                        // key_file
        S_392_48 = 392,                          // $@48
        S_cipher_list = 393,                     // cipher_list
        S_394_49 = 394,                          // $@49
        S_host_reservation_identifiers = 395,    // host_reservation_identifiers
        S_396_50 = 396,                          // $@50
        S_host_reservation_identifiers_list = 397, // host_reservation_identifiers_list
        S_host_reservation_identifier = 398,     // host_reservation_identifier
        S_duid_id = 399,                         // duid_id
        S_hw_address_id = 400,                   // hw_address_id
        S_circuit_id = 401,                      // circuit_id
        S_client_id = 402,                       // client_id
        S_flex_id = 403,                         // flex_id
        S_dhcp_multi_threading = 404,            // dhcp_multi_threading
        S_405_51 = 405,                          // $@51
        S_multi_threading_params = 406,          // multi_threading_params
        S_multi_threading_param = 407,           // multi_threading_param
        S_enable_multi_threading = 408,          // enable_multi_threading
        S_thread_pool_size = 409,                // thread_pool_size
        S_packet_queue_size = 410,               // packet_queue_size
        S_hooks_libraries = 411,                 // hooks_libraries
        S_412_52 = 412,                          // $@52
        S_hooks_libraries_list = 413,            // hooks_libraries_list
        S_not_empty_hooks_libraries_list = 414,  // not_empty_hooks_libraries_list
        S_hooks_library = 415,                   // hooks_library
        S_416_53 = 416,                          // $@53
        S_sub_hooks_library = 417,               // sub_hooks_library
        S_418_54 = 418,                          // $@54
        S_hooks_params = 419,                    // hooks_params
        S_hooks_param = 420,                     // hooks_param
        S_library = 421,                         // library
        S_422_55 = 422,                          // $@55
        S_parameters = 423,                      // parameters
        S_424_56 = 424,                          // $@56
        S_expired_leases_processing = 425,       // expired_leases_processing
        S_426_57 = 426,                          // $@57
        S_expired_leases_params = 427,           // expired_leases_params
        S_expired_leases_param = 428,            // expired_leases_param
        S_reclaim_timer_wait_time = 429,         // reclaim_timer_wait_time
        S_flush_reclaimed_timer_wait_time = 430, // flush_reclaimed_timer_wait_time
        S_hold_reclaimed_time = 431,             // hold_reclaimed_time
        S_max_reclaim_leases = 432,              // max_reclaim_leases
        S_max_reclaim_time = 433,                // max_reclaim_time
        S_unwarned_reclaim_cycles = 434,         // unwarned_reclaim_cycles
        S_subnet4_list = 435,                    // subnet4_list
        S_436_58 = 436,                          // $@58
        S_subnet4_list_content = 437,            // subnet4_list_content
        S_not_empty_subnet4_list = 438,          // not_empty_subnet4_list
        S_subnet4 = 439,                         // subnet4
        S_440_59 = 440,                          // $@59
        S_sub_subnet4 = 441,                     // sub_subnet4
        S_442_60 = 442,                          // $@60
        S_subnet4_params = 443,                  // subnet4_params
        S_subnet4_param = 444,                   // subnet4_param
        S_subnet = 445,                          // subnet
        S_446_61 = 446,                          // $@61
        S_subnet_4o6_interface = 447,            // subnet_4o6_interface
        S_448_62 = 448,                          // $@62
        S_subnet_4o6_interface_id = 449,         // subnet_4o6_interface_id
        S_450_63 = 450,                          // $@63
        S_subnet_4o6_subnet = 451,               // subnet_4o6_subnet
        S_452_64 = 452,                          // $@64
        S_interface = 453,                       // interface
        S_454_65 = 454,                          // $@65
        S_client_class = 455,                    // client_class
        S_456_66 = 456,                          // $@66
        S_network_client_classes = 457,          // network_client_classes
        S_458_67 = 458,                          // $@67
        S_require_client_classes = 459,          // require_client_classes
        S_460_68 = 460,                          // $@68
        S_evaluate_additional_classes = 461,     // evaluate_additional_classes
        S_462_69 = 462,                          // $@69
        S_reservations_global = 463,             // reservations_global
        S_reservations_in_subnet = 464,          // reservations_in_subnet
        S_reservations_out_of_pool = 465,        // reservations_out_of_pool
        S_id = 466,                              // id
        S_shared_networks = 467,                 // shared_networks
        S_468_70 = 468,                          // $@70
        S_shared_networks_content = 469,         // shared_networks_content
        S_shared_networks_list = 470,            // shared_networks_list
        S_shared_network = 471,                  // shared_network
        S_472_71 = 472,                          // $@71
        S_shared_network_params = 473,           // shared_network_params
        S_shared_network_param = 474,            // shared_network_param
        S_option_def_list = 475,                 // option_def_list
        S_476_72 = 476,                          // $@72
        S_sub_option_def_list = 477,             // sub_option_def_list
        S_478_73 = 478,                          // $@73
        S_option_def_list_content = 479,         // option_def_list_content
        S_not_empty_option_def_list = 480,       // not_empty_option_def_list
        S_option_def_entry = 481,                // option_def_entry
        S_482_74 = 482,                          // $@74
        S_sub_option_def = 483,                  // sub_option_def
        S_484_75 = 484,                          // $@75
        S_option_def_params = 485,               // option_def_params
        S_not_empty_option_def_params = 486,     // not_empty_option_def_params
        S_option_def_param = 487,                // option_def_param
        S_option_def_name = 488,                 // option_def_name
        S_code = 489,                            // code
        S_option_def_code = 490,                 // option_def_code
        S_option_def_type = 491,                 // option_def_type
        S_492_76 = 492,                          // $@76
        S_option_def_record_types = 493,         // option_def_record_types
        S_494_77 = 494,                          // $@77
        S_space = 495,                           // space
        S_496_78 = 496,                          // $@78
        S_option_def_space = 497,                // option_def_space
        S_option_def_encapsulate = 498,          // option_def_encapsulate
        S_499_79 = 499,                          // $@79
        S_option_def_array = 500,                // option_def_array
        S_option_data_list = 501,                // option_data_list
        S_502_80 = 502,                          // $@80
        S_option_data_list_content = 503,        // option_data_list_content
        S_not_empty_option_data_list = 504,      // not_empty_option_data_list
        S_option_data_entry = 505,               // option_data_entry
        S_506_81 = 506,                          // $@81
        S_sub_option_data = 507,                 // sub_option_data
        S_508_82 = 508,                          // $@82
        S_option_data_params = 509,              // option_data_params
        S_not_empty_option_data_params = 510,    // not_empty_option_data_params
        S_option_data_param = 511,               // option_data_param
        S_option_data_name = 512,                // option_data_name
        S_option_data_data = 513,                // option_data_data
        S_514_83 = 514,                          // $@83
        S_option_data_code = 515,                // option_data_code
        S_option_data_space = 516,               // option_data_space
        S_option_data_csv_format = 517,          // option_data_csv_format
        S_option_data_always_send = 518,         // option_data_always_send
        S_option_data_never_send = 519,          // option_data_never_send
        S_option_data_client_classes = 520,      // option_data_client_classes
        S_521_84 = 521,                          // $@84
        S_pools_list = 522,                      // pools_list
        S_523_85 = 523,                          // $@85
        S_pools_list_content = 524,              // pools_list_content
        S_not_empty_pools_list = 525,            // not_empty_pools_list
        S_pool_list_entry = 526,                 // pool_list_entry
        S_527_86 = 527,                          // $@86
        S_sub_pool4 = 528,                       // sub_pool4
        S_529_87 = 529,                          // $@87
        S_pool_params = 530,                     // pool_params
        S_pool_param = 531,                      // pool_param
        S_pool_entry = 532,                      // pool_entry
        S_533_88 = 533,                          // $@88
        S_pool_id = 534,                         // pool_id
        S_user_context = 535,                    // user_context
        S_536_89 = 536,                          // $@89
        S_comment = 537,                         // comment
        S_538_90 = 538,                          // $@90
        S_reservations = 539,                    // reservations
        S_540_91 = 540,                          // $@91
        S_reservations_list = 541,               // reservations_list
        S_not_empty_reservations_list = 542,     // not_empty_reservations_list
        S_reservation = 543,                     // reservation
        S_544_92 = 544,                          // $@92
        S_sub_reservation = 545,                 // sub_reservation
        S_546_93 = 546,                          // $@93
        S_reservation_params = 547,              // reservation_params
        S_not_empty_reservation_params = 548,    // not_empty_reservation_params
        S_reservation_param = 549,               // reservation_param
        S_next_server = 550,                     // next_server
        S_551_94 = 551,                          // $@94
        S_server_hostname = 552,                 // server_hostname
        S_553_95 = 553,                          // $@95
        S_boot_file_name = 554,                  // boot_file_name
        S_555_96 = 555,                          // $@96
        S_ip_address = 556,                      // ip_address
        S_557_97 = 557,                          // $@97
        S_duid = 558,                            // duid
        S_559_98 = 559,                          // $@98
        S_hw_address = 560,                      // hw_address
        S_561_99 = 561,                          // $@99
        S_client_id_value = 562,                 // client_id_value
        S_563_100 = 563,                         // $@100
        S_circuit_id_value = 564,                // circuit_id_value
        S_565_101 = 565,                         // $@101
        S_flex_id_value = 566,                   // flex_id_value
        S_567_102 = 567,                         // $@102
        S_hostname = 568,                        // hostname
        S_569_103 = 569,                         // $@103
        S_reservation_client_classes = 570,      // reservation_client_classes
        S_571_104 = 571,                         // $@104
        S_relay = 572,                           // relay
        S_573_105 = 573,                         // $@105
        S_relay_map = 574,                       // relay_map
        S_ip_addresses = 575,                    // ip_addresses
        S_576_106 = 576,                         // $@106
        S_client_classes = 577,                  // client_classes
        S_578_107 = 578,                         // $@107
        S_client_classes_list = 579,             // client_classes_list
        S_client_class_entry = 580,              // client_class_entry
        S_581_108 = 581,                         // $@108
        S_client_class_params = 582,             // client_class_params
        S_not_empty_client_class_params = 583,   // not_empty_client_class_params
        S_client_class_param = 584,              // client_class_param
        S_client_class_name = 585,               // client_class_name
        S_client_class_test = 586,               // client_class_test
        S_587_109 = 587,                         // $@109
        S_client_class_template_test = 588,      // client_class_template_test
        S_589_110 = 589,                         // $@110
        S_only_if_required = 590,                // only_if_required
        S_only_in_additional_list = 591,         // only_in_additional_list
        S_dhcp4o6_port = 592,                    // dhcp4o6_port
        S_control_socket = 593,                  // control_socket
        S_594_111 = 594,                         // $@111
        S_control_sockets = 595,                 // control_sockets
        S_596_112 = 596,                         // $@112
        S_control_socket_list = 597,             // control_socket_list
        S_not_empty_control_socket_list = 598,   // not_empty_control_socket_list
        S_control_socket_entry = 599,            // control_socket_entry
        S_600_113 = 600,                         // $@113
        S_control_socket_params = 601,           // control_socket_params
        S_control_socket_param = 602,            // control_socket_param
        S_control_socket_type = 603,             // control_socket_type
        S_604_114 = 604,                         // $@114
        S_control_socket_type_value = 605,       // control_socket_type_value
        S_control_socket_name = 606,             // control_socket_name
        S_607_115 = 607,                         // $@115
        S_control_socket_address = 608,          // control_socket_address
        S_609_116 = 609,                         // $@116
        S_control_socket_port = 610,             // control_socket_port
        S_cert_required = 611,                   // cert_required
        S_http_headers = 612,                    // http_headers
        S_613_117 = 613,                         // $@117
        S_http_header_list = 614,                // http_header_list
        S_not_empty_http_header_list = 615,      // not_empty_http_header_list
        S_http_header = 616,                     // http_header
        S_617_118 = 617,                         // $@118
        S_http_header_params = 618,              // http_header_params
        S_http_header_param = 619,               // http_header_param
        S_header_value = 620,                    // header_value
        S_621_119 = 621,                         // $@119
        S_authentication = 622,                  // authentication
        S_623_120 = 623,                         // $@120
        S_auth_params = 624,                     // auth_params
        S_auth_param = 625,                      // auth_param
        S_auth_type = 626,                       // auth_type
        S_627_121 = 627,                         // $@121
        S_auth_type_value = 628,                 // auth_type_value
        S_realm = 629,                           // realm
        S_630_122 = 630,                         // $@122
        S_directory = 631,                       // directory
        S_632_123 = 632,                         // $@123
        S_clients = 633,                         // clients
        S_634_124 = 634,                         // $@124
        S_clients_list = 635,                    // clients_list
        S_not_empty_clients_list = 636,          // not_empty_clients_list
        S_basic_auth = 637,                      // basic_auth
        S_638_125 = 638,                         // $@125
        S_clients_params = 639,                  // clients_params
        S_clients_param = 640,                   // clients_param
        S_user_file = 641,                       // user_file
        S_642_126 = 642,                         // $@126
        S_password_file = 643,                   // password_file
        S_644_127 = 644,                         // $@127
        S_dhcp_queue_control = 645,              // dhcp_queue_control
        S_646_128 = 646,                         // $@128
        S_queue_control_params = 647,            // queue_control_params
        S_queue_control_param = 648,             // queue_control_param
        S_enable_queue = 649,                    // enable_queue
        S_queue_type = 650,                      // queue_type
        S_651_129 = 651,                         // $@129
        S_capacity = 652,                        // capacity
        S_arbitrary_map_entry = 653,             // arbitrary_map_entry
        S_654_130 = 654,                         // $@130
        S_dhcp_ddns = 655,                       // dhcp_ddns
        S_656_131 = 656,                         // $@131
        S_sub_dhcp_ddns = 657,                   // sub_dhcp_ddns
        S_658_132 = 658,                         // $@132
        S_dhcp_ddns_params = 659,                // dhcp_ddns_params
        S_dhcp_ddns_param = 660,                 // dhcp_ddns_param
        S_enable_updates = 661,                  // enable_updates
        S_server_ip = 662,                       // server_ip
        S_663_133 = 663,                         // $@133
        S_server_port = 664,                     // server_port
        S_sender_ip = 665,                       // sender_ip
        S_666_134 = 666,                         // $@134
        S_sender_port = 667,                     // sender_port
        S_max_queue_size = 668,                  // max_queue_size
        S_ncr_protocol = 669,                    // ncr_protocol
        S_670_135 = 670,                         // $@135
        S_ncr_protocol_value = 671,              // ncr_protocol_value
        S_ncr_format = 672,                      // ncr_format
        S_673_136 = 673,                         // $@136
        S_config_control = 674,                  // config_control
        S_675_137 = 675,                         // $@137
        S_sub_config_control = 676,              // sub_config_control
        S_677_138 = 677,                         // $@138
        S_config_control_params = 678,           // config_control_params
        S_config_control_param = 679,            // config_control_param
        S_config_databases = 680,                // config_databases
        S_681_139 = 681,                         // $@139
        S_config_fetch_wait_time = 682,          // config_fetch_wait_time
        S_loggers = 683,                         // loggers
        S_684_140 = 684,                         // $@140
        S_loggers_entries = 685,                 // loggers_entries
        S_logger_entry = 686,                    // logger_entry
        S_687_141 = 687,                         // $@141
        S_logger_params = 688,                   // logger_params
        S_logger_param = 689,                    // logger_param
        S_debuglevel = 690,                      // debuglevel
        S_severity = 691,                        // severity
        S_692_142 = 692,                         // $@142
        S_output_options_list = 693,             // output_options_list
        S_694_143 = 694,                         // $@143
        S_output_options_list_content = 695,     // output_options_list_content
        S_output_entry = 696,                    // output_entry
        S_697_144 = 697,                         // $@144
        S_output_params_list = 698,              // output_params_list
        S_output_params = 699,                   // output_params
        S_output = 700,                          // output
        S_701_145 = 701,                         // $@145
        S_flush = 702,                           // flush
        S_maxsize = 703,                         // maxsize
        S_maxver = 704,                          // maxver
        S_pattern = 705,                         // pattern
        S_706_146 = 706,                         // $@146
        S_compatibility = 707,                   // compatibility
        S_708_147 = 708,                         // $@147
        S_compatibility_params = 709,            // compatibility_params
        S_compatibility_param = 710,             // compatibility_param
        S_lenient_option_parsing = 711,          // lenient_option_parsing
        S_ignore_dhcp_server_identifier = 712,   // ignore_dhcp_server_identifier
        S_ignore_rai_link_selection = 713,       // ignore_rai_link_selection
        S_exclude_first_last_24 = 714            // exclude_first_last_24
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
        return Dhcp4Parser::symbol_name (this->kind ());
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
        PARSER4__ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_PARSER4_error <= tok && tok <= token::TOKEN_SUB_CONFIG_CONTROL));
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
        PARSER4__ASSERT (tok == token::TOKEN_BOOLEAN);
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
        PARSER4__ASSERT (tok == token::TOKEN_FLOAT);
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
        PARSER4__ASSERT (tok == token::TOKEN_INTEGER);
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
        PARSER4__ASSERT (tok == token::TOKEN_STRING);
#endif
      }
    };

    /// Build a parser object.
    Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg);
    virtual ~Dhcp4Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Dhcp4Parser (const Dhcp4Parser&) = delete;
    /// Non copyable.
    Dhcp4Parser& operator= (const Dhcp4Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if PARSER4_DEBUG
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
      make_PARSER4_error (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER4_error, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER4_error (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER4_error, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PARSER4_UNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_PARSER4_UNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_PARSER4_UNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_PARSER4_UNDEF, l);
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
      make_DHCP_SOCKET_TYPE (location_type l)
      {
        return symbol_type (token::TOKEN_DHCP_SOCKET_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_DHCP_SOCKET_TYPE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DHCP_SOCKET_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RAW (location_type l)
      {
        return symbol_type (token::TOKEN_RAW, std::move (l));
      }
#else
      static
      symbol_type
      make_RAW (const location_type& l)
      {
        return symbol_type (token::TOKEN_RAW, l);
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
      make_OUTBOUND_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_OUTBOUND_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_OUTBOUND_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OUTBOUND_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SAME_AS_INBOUND (location_type l)
      {
        return symbol_type (token::TOKEN_SAME_AS_INBOUND, std::move (l));
      }
#else
      static
      symbol_type
      make_SAME_AS_INBOUND (const location_type& l)
      {
        return symbol_type (token::TOKEN_SAME_AS_INBOUND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USE_ROUTING (location_type l)
      {
        return symbol_type (token::TOKEN_USE_ROUTING, std::move (l));
      }
#else
      static
      symbol_type
      make_USE_ROUTING (const location_type& l)
      {
        return symbol_type (token::TOKEN_USE_ROUTING, l);
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
      make_ECHO_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_ECHO_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_ECHO_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_ECHO_CLIENT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MATCH_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_MATCH_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_MATCH_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_MATCH_CLIENT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTHORITATIVE (location_type l)
      {
        return symbol_type (token::TOKEN_AUTHORITATIVE, std::move (l));
      }
#else
      static
      symbol_type
      make_AUTHORITATIVE (const location_type& l)
      {
        return symbol_type (token::TOKEN_AUTHORITATIVE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEXT_SERVER (location_type l)
      {
        return symbol_type (token::TOKEN_NEXT_SERVER, std::move (l));
      }
#else
      static
      symbol_type
      make_NEXT_SERVER (const location_type& l)
      {
        return symbol_type (token::TOKEN_NEXT_SERVER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SERVER_HOSTNAME (location_type l)
      {
        return symbol_type (token::TOKEN_SERVER_HOSTNAME, std::move (l));
      }
#else
      static
      symbol_type
      make_SERVER_HOSTNAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_SERVER_HOSTNAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOT_FILE_NAME (location_type l)
      {
        return symbol_type (token::TOKEN_BOOT_FILE_NAME, std::move (l));
      }
#else
      static
      symbol_type
      make_BOOT_FILE_NAME (const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOT_FILE_NAME, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OFFER_LFT (location_type l)
      {
        return symbol_type (token::TOKEN_OFFER_LFT, std::move (l));
      }
#else
      static
      symbol_type
      make_OFFER_LFT (const location_type& l)
      {
        return symbol_type (token::TOKEN_OFFER_LFT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STASH_AGENT_OPTIONS (location_type l)
      {
        return symbol_type (token::TOKEN_STASH_AGENT_OPTIONS, std::move (l));
      }
#else
      static
      symbol_type
      make_STASH_AGENT_OPTIONS (const location_type& l)
      {
        return symbol_type (token::TOKEN_STASH_AGENT_OPTIONS, l);
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
      make_DDNS_TTL (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_TTL (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_TTL_MIN (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_MIN, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_TTL_MIN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_MIN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DDNS_TTL_MAX (location_type l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_MAX, std::move (l));
      }
#else
      static
      symbol_type
      make_DDNS_TTL_MAX (const location_type& l)
      {
        return symbol_type (token::TOKEN_DDNS_TTL_MAX, l);
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
      make_SUBNET4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE_ID (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_INTERFACE_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_INTERFACE_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUBNET_4O6_SUBNET (location_type l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_SUBNET, std::move (l));
      }
#else
      static
      symbol_type
      make_SUBNET_4O6_SUBNET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUBNET_4O6_SUBNET, l);
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
      make_CIRCUIT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_CIRCUIT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_CIRCUIT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CIRCUIT_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLIENT_ID (location_type l)
      {
        return symbol_type (token::TOKEN_CLIENT_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_CLIENT_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_CLIENT_ID, l);
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
      make_IGNORE_DHCP_SERVER_ID (location_type l)
      {
        return symbol_type (token::TOKEN_IGNORE_DHCP_SERVER_ID, std::move (l));
      }
#else
      static
      symbol_type
      make_IGNORE_DHCP_SERVER_ID (const location_type& l)
      {
        return symbol_type (token::TOKEN_IGNORE_DHCP_SERVER_ID, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IGNORE_RAI_LINK_SEL (location_type l)
      {
        return symbol_type (token::TOKEN_IGNORE_RAI_LINK_SEL, std::move (l));
      }
#else
      static
      symbol_type
      make_IGNORE_RAI_LINK_SEL (const location_type& l)
      {
        return symbol_type (token::TOKEN_IGNORE_RAI_LINK_SEL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXCLUDE_FIRST_LAST_24 (location_type l)
      {
        return symbol_type (token::TOKEN_EXCLUDE_FIRST_LAST_24, std::move (l));
      }
#else
      static
      symbol_type
      make_EXCLUDE_FIRST_LAST_24 (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXCLUDE_FIRST_LAST_24, l);
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
      make_TOPLEVEL_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_TOPLEVEL_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_TOPLEVEL_DHCP4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_DHCP4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_DHCP4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_DHCP4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_INTERFACES4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_INTERFACES4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_INTERFACES4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_SUBNET4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_SUBNET4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_SUBNET4, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_POOL4 (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_POOL4, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB_POOL4 (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_POOL4, l);
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
      context (const Dhcp4Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Dhcp4Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Dhcp4Parser (const Dhcp4Parser&);
    /// Non copyable.
    Dhcp4Parser& operator= (const Dhcp4Parser&);
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


#if PARSER4_DEBUG
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
      yylast_ = 1448,     ///< Last index in yytable_.
      yynnts_ = 481,  ///< Number of nonterminal symbols.
      yyfinal_ = 28 ///< Termination state number.
    };


    // User arguments.
    isc::dhcp::Parser4Context& ctx;

  };

  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::yytranslate_ (int t) YY_NOEXCEPT
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
     225,   226,   227,   228,   229,   230,   231,   232,   233
    };
    // Last valid token kind.
    const int code_max = 488;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Dhcp4Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Dhcp4Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Dhcp4Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_ddns_conflict_resolution_mode_value: // ddns_conflict_resolution_mode_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_on_fail_mode: // on_fail_mode
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
  Dhcp4Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Dhcp4Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Dhcp4Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Dhcp4Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Dhcp4Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Dhcp4Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5963 "dhcp4_parser.h"




#endif // !YY_PARSER4_DHCP4_PARSER_H_INCLUDED
